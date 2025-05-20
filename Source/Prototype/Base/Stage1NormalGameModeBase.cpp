// Fill out your copyright notice in the Description page of Project Settings.

#include "Base/Stage1NormalGameModeBase.h"
#include "../Component/StatComponent.h"
#include "../Component/InventoryComponent.h"
#include "../Player/Portal/Portal_Home.h"
#include "MyGameInstance.h"
#include "../Player/MyPlayer.h"
#include "../Base/Managers/UIManager.h"
#include "../Monster/BossMonster.h"
#include "../Monster/AI/AIController_BossMonster.h"
#include "UI/Boss1Widget.h"
#include "UI/SkillWidget_test.h"
#include "Kismet/GameplayStatics.h"

AStage1NormalGameModeBase::AStage1NormalGameModeBase()
{
}

void AStage1NormalGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	AMyPlayer *player = Cast<AMyPlayer>(UGameplayStatics::GetPlayerCharacter(this, 0));
	if (player)
	{
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
}

void AStage1NormalGameModeBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}
