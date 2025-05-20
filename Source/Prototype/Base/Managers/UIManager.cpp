// Fill out your copyright notice in the Description page of Project Settings.

#include "Base/Managers/UIManager.h"

#include "UI/InventoryWidget.h"
#include "UI/Boss1Widget.h"
#include "UI/Boss2Widget.h"
#include "UI/ShopWidget.h"
#include "UI/MainStartWidget.h"
#include "Kismet/GameplayStatics.h"

#include "TriggerBox_StageSequnce/StageSequence_Trigger.h"

// Sets default values
AUIManager::AUIManager()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	static ConstructorHelpers::FClassFinder<UUserWidget> inventory(
		TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Blueprint/UI/Inventory_UI.Inventory_UI_C'"));
	if (inventory.Succeeded())
	{
		_inventoryUI = CreateWidget<UInventoryWidget>(GetWorld(), inventory.Class);
	}

	static ConstructorHelpers::FClassFinder<UUserWidget> boss1widget(
		TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Blueprint/UI/Boss_UI.Boss_UI_C'"));
	if (boss1widget.Succeeded())
	{
		_bossUI = CreateWidget<UBoss1Widget>(GetWorld(), boss1widget.Class);
	}

	static ConstructorHelpers::FClassFinder<UUserWidget> boss2widget(
		TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Blueprint/UI/Boss2_UI.Boss2_UI_C'"));
	if (boss2widget.Succeeded())
	{
		_boss2UI = CreateWidget<UBoss2Widget>(GetWorld(), boss2widget.Class);
	}

	static ConstructorHelpers::FClassFinder<UUserWidget> shopUI(
		TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Blueprint/UI/Shop_UI.Shop_UI_C'"));
	if (shopUI.Succeeded())
	{
		_shopUI = CreateWidget<UShopWidget>(GetWorld(), shopUI.Class);
	}

	static ConstructorHelpers::FClassFinder<UUserWidget> StartWidget(
		TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Blueprint/UI/MainStart_UI.MainStart_UI_C'"));
	if (StartWidget.Succeeded())
	{
		_startUI = CreateWidget<UMainStartWidget>(GetWorld(), StartWidget.Class);
	}

	static ConstructorHelpers::FClassFinder<UUserWidget> LoadWidget(
		TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Blueprint/UI/Widget_Info.Widget_Info_C'"));
	if (LoadWidget.Succeeded())
	{
		_loadUI = CreateWidget<UUserWidget>(GetWorld(), LoadWidget.Class);
	}

	static ConstructorHelpers::FClassFinder<UUserWidget> OptionsWidget(
		TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Blueprint/UI/options_UITEST.options_UITEST_C'"));
	if (OptionsWidget.Succeeded())
	{
		_options = CreateWidget<UUserWidget>(GetWorld(), OptionsWidget.Class);
	}

	static ConstructorHelpers::FObjectFinder<UTexture2D> defaultTexture(
		TEXT("/Script/Engine.Texture2D'/Game/CraftResourcesIcons/Textures/T_Default.T_Default'"));
	if (defaultTexture.Succeeded())
	{
		_defaultTexture = defaultTexture.Object;
	}




	

	_uiList.Add(_inventoryUI);
	_uiIsOpen.Add(false);
	_isPauseWhenOpen.Add(true);

	_uiList.Add(_bossUI);
	_uiIsOpen.Add(false);
	_isPauseWhenOpen.Add(false);

	_uiList.Add(_boss2UI);
	_uiIsOpen.Add(false);
	_isPauseWhenOpen.Add(false);

	_uiList.Add(_shopUI);
	_uiIsOpen.Add(false);
	_isPauseWhenOpen.Add(true);

	_uiList.Add(_startUI);
	_uiIsOpen.Add(false);
	_isPauseWhenOpen.Add(true);

	_uiList.Add(_loadUI);
	_uiIsOpen.Add(false);
	_isPauseWhenOpen.Add(false);

	_uiList.Add(_options);
	_uiIsOpen.Add(false);
	_isPauseWhenOpen.Add(true);
}

// Called when the game starts or when spawned
void AUIManager::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AUIManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AUIManager::OpenUI(UI_LIST ui)
{
	int32 UIindex = (int32)ui;
	if (UIindex > _uiList.Num())
		return;

	if (InventoryMutual(ui) || InterectMutual(ui))
		return;

	if (_isPauseWhenOpen[UIindex])
		pauseGame.Broadcast();

	if(ui == UI_LIST::Options)
		UGameplayStatics::SetGamePaused(GetWorld(), true);

	APlayerController *PlayerController = GetWorld()->GetFirstPlayerController();
	if (PlayerController)
	{
		bool bIsCursorVisible = PlayerController->bShowMouseCursor;
		PlayerController->bShowMouseCursor = true;
		PlayerController->SetInputMode(FInputModeGameAndUI().SetHideCursorDuringCapture(false));
	}

	_uiList[UIindex]->SetVisibility(ESlateVisibility::Visible);
	int32 ZOrder = (ui == UI_LIST::Inventory) ? 10 : 0;
	_uiList[UIindex]->AddToViewport(ZOrder);

	_uiIsOpen[UIindex] = true;
}

void AUIManager::CloseUI(UI_LIST ui)
{
	int32 UIindex = (int32)ui;
	if (UIindex > _uiList.Num())
		return;

	if (_isPauseWhenOpen[UIindex])
		resumGame.Broadcast();

	_uiList[UIindex]->SetVisibility(ESlateVisibility::Hidden);
	_uiList[UIindex]->RemoveFromParent();

	_uiIsOpen[UIindex] = false;

	APlayerController *PlayerController = GetWorld()->GetFirstPlayerController();
	if (PlayerController)
	{
		PlayerController->bShowMouseCursor = false;
		PlayerController->SetInputMode(FInputModeGameOnly());
	}
}

void AUIManager::CloseAll()
{
	resumGame.Broadcast();

	for (auto widget : _uiList)
	{
		if(widget)
		{
			widget->SetVisibility(ESlateVisibility::Hidden);
			widget->RemoveFromParent();
		}
		
	}
	for (bool isopen : _uiIsOpen)
		isopen = false;
}

void AUIManager::ToggleUI(UI_LIST ui)
{
	int32 UIindex = (int32)ui;
	if (UIindex > _uiList.Num())
		return;

	if (_uiIsOpen[UIindex])
		CloseUI(ui);
	else
		OpenUI(ui);
}

bool AUIManager::InventoryMutual(UI_LIST invenUI)
{
	if(invenUI != UI_LIST::Inventory)
		return false;
	if (_uiIsOpen[(int32)UI_LIST::Shop])
		return true;
	return false;
}

bool AUIManager::InterectMutual(UI_LIST interectUI)
{
	if (interectUI != UI_LIST::Shop)
		return false;
	if (_uiIsOpen[(int32)UI_LIST::Inventory])
		return true;
	return false;
}
