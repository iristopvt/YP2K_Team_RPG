// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MainStartWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Components/Button.h"
#include "Base/Managers/UIManager.h"
#include "Base/MyGameInstance.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Blueprint/UserWidget.h"
#include "UObject/ConstructorHelpers.h"



UMainStartWidget::UMainStartWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	static ConstructorHelpers::FClassFinder<UUserWidget> Options
	(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Blueprint/UI/options_UITEST.options_UITEST_C'"));
	if (Options.Succeeded())
	{
		_OptionsButton = Options.Class;
	}
}

void UMainStartWidget::NativeConstruct()
{

	Super::NativeConstruct();

	if (StartButton)
	{
		StartButton->OnClicked.AddDynamic(this, &UMainStartWidget::StartButtonClick);
	}
	if (QuitButton)
	{
		QuitButton->OnClicked.AddDynamic(this, &UMainStartWidget::QuitButtonClick);
	}

	if (OptionsButton)
	{
		OptionsButton->OnClicked.AddDynamic(this, &UMainStartWidget::OptionsButtonClick);
	}

}

void UMainStartWidget::StartButtonClick()
{
	UIManager->OpenUI(UI_LIST::Load);
	
	 FTimerHandle TimerHandle;
    GetWorld()->GetTimerManager().SetTimer(
        TimerHandle, 
        this, 
        &UMainStartWidget::OpenLevel, 
        2.0f, 
        false
    );
}

void UMainStartWidget::QuitButtonClick()
{
	UKismetSystemLibrary::QuitGame(GetWorld(), GetWorld()->GetFirstPlayerController(), EQuitPreference::Quit, true);
}

void UMainStartWidget::OptionsButtonClick()
{
	if (_OptionsButton)
	{
		UUserWidget* Optionss = CreateWidget<UUserWidget>(GetWorld(), _OptionsButton);
		if (Optionss)
		{
			Optionss->AddToViewport();
		}
	}
}

void UMainStartWidget::OpenLevel()
{
	 UGameplayStatics::OpenLevel(GetWorld(), TEXT("NewMap"));
}

