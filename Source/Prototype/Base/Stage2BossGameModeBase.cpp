// Fill out your copyright notice in the Description page of Project Settings.


#include "Base/Stage2BossGameModeBase.h"
#include "Component/StatComponent.h"
#include "Component/InventoryComponent.h"
#include "../Player/Portal/Portal_Home.h"
#include "MyGameInstance.h"
#include "../Player/MyPlayer.h"
#include "../Player/MyPlayerController.h"
#include "Base/Managers/UIManager.h"
#include "../Monster/Boss2Monster.h"
#include "../Monster/SunderPool.h"
#include "../Monster/BossSunder.h"
#include "../Monster/AI/AIController_Boss2.h"
#include "UI/Boss2Widget.h"
#include "UI/SkillWidget_test.h"
#include "Kismet/GameplayStatics.h"


AStage2BossGameModeBase::AStage2BossGameModeBase()
{
    static ConstructorHelpers::FClassFinder<ABoss2Monster> BM(TEXT("/Script/Engine.Blueprint'/Game/Blueprint/Monster/BossMonster/Boss2_BP.Boss2_BP_C'"));
	if (BM.Succeeded())
	{
		_boss = BM.Class;
	}

	static ConstructorHelpers::FClassFinder<APortal_Home> PH(TEXT("/Script/Engine.Blueprint'/Game/Blueprint/Player/Portal/HomePortal_BP.HomePortal_BP_C'"));
	if (PH.Succeeded())
	{
		_portal = PH.Class;
	}
}

void AStage2BossGameModeBase::BeginPlay()
{
    Super::BeginPlay();

	AMyPlayer *player = Cast<AMyPlayer>(UGameplayStatics::GetPlayerCharacter(this, 0));
	if (player)
	{
		FTimerHandle TimerHandle;
		GetWorldTimerManager().SetTimer(TimerHandle, this, &AStage2BossGameModeBase::LockSkill, 0.1f, false);
		UMyGameInstance *GameInstance = Cast<UMyGameInstance>(GetGameInstance());
		if (GameInstance)
		{
			GameInstance->InitializeManagers();
			UStatComponent *StatComponent = player->FindComponentByClass<UStatComponent>();
			if (StatComponent)
			{
				GameInstance->LoadPlayerStats(StatComponent);
			}

			UInventoryComponent *InvenComponent = player->FindComponentByClass<UInventoryComponent>();
			if (InvenComponent)
			{
				GameInstance->LoadInventory(InvenComponent);
			}
			GameInstance->LoadPlayerSkeletal(player);

			APlayerController *PlayerController = GetWorld()->GetFirstPlayerController();
			if (PlayerController)
			{
				PlayerController->bShowMouseCursor = false;
				PlayerController->SetInputMode(FInputModeGameOnly());
			}
		}
	}

	FActorSpawnParameters SpawnParams;
	SpawnParams.Name = TEXT("Boss2");
	
	ABoss2Monster *Boss = GetWorld()->SpawnActor<ABoss2Monster>(_boss, FVector(141.0f, -3893.1f, 429.9f), FRotator::ZeroRotator, SpawnParams);
	if (Boss)
	{
		Boss->_StatCom->SetBossLevelInit(1);
		AAIController_Boss2 *BossAI = GetWorld()->SpawnActor<AAIController_Boss2>(AAIController_Boss2::StaticClass());
		if (BossAI)
		{
			BossAI->OnPossess(Boss);
		}

		UIManager->OpenUI(UI_LIST::Boss2);
		APlayerController *PlayerController = GetWorld()->GetFirstPlayerController();
		if (PlayerController)
		{
			PlayerController->bShowMouseCursor = false;
			PlayerController->SetInputMode(FInputModeGameOnly());
		}

		Boss->_StatCom->_PlHPDelegate.AddUObject(UIManager->GetBoss2UI(), &UBoss2Widget::UpdateBossHPBar);
		Boss->_StatCom->_deathDelegate.AddUObject(this, &AStage2BossGameModeBase::BossClear);
	}


}

void AStage2BossGameModeBase::PostInitializeComponents()
{
    Super::PostInitializeComponents();
}

void AStage2BossGameModeBase::BossClear()
{
	if (_portal)
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.Name = TEXT("PortalHome");

		FVector PortalLocation = FVector(40.0f, -3230.1f, 190.9f);
		FRotator PortalRotation = FRotator::ZeroRotator;

		APortal_Home *Portal = GetWorld()->SpawnActor<APortal_Home>(_portal, PortalLocation, PortalRotation, SpawnParams);
	}
}

void AStage2BossGameModeBase::BossStart()
{
	UE_LOG(LogTemp, Warning, TEXT("Boss Start"));
	AMyPlayer *player = Cast<AMyPlayer>(UGameplayStatics::GetPlayerCharacter(this, 0));
	if (player)
	{
		FVector NewLocation = FVector(50.0f, -1420.f, 226.f);
		FRotator NewRotation = FRotator::ZeroRotator;

		APlayerController *PlayerController = GetWorld()->GetFirstPlayerController();
		if (PlayerController)
		{
			PlayerController->bShowMouseCursor = false;
			PlayerController->SetInputMode(FInputModeGameOnly());
		}
		player->_skillWidgetInstance->UnLockAllSkill();
		player->SetActorLocationAndRotation(NewLocation, NewRotation);
	}

}

void AStage2BossGameModeBase::LockSkill()
{
	AMyPlayerController* PlayerController = Cast<AMyPlayerController>(GetWorld()->GetFirstPlayerController());
	if (PlayerController && PlayerController->SkillWidgetInstance)
	{
		PlayerController->SkillWidgetInstance->LockAllSkill(); 
	}
}


