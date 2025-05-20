// Fill out your copyright notice in the Description page of Project Settings.

#include "TriggerBox_StageSequnce/StageSequence_Trigger.h"
#include "Base/MyGameInstance.h"
#include "Base/Managers/UIManager.h"
#include "Base/Stage1BossGameModeBase.h"


// Sets default values
AStageSequence_Trigger::AStageSequence_Trigger()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AStageSequence_Trigger::BeginPlay()
{
    Super::BeginPlay();

}

void AStageSequence_Trigger::OnSequenceFinished()
{
   Super::OnSequenceFinished();
   UIManager->OpenUI(UI_LIST::Boss);

    AStage1BossGameModeBase *GameMode = Cast<AStage1BossGameModeBase>(GetWorld()->GetAuthGameMode());
    if (GameMode)
    {
        GameMode->BossStart();
    }
}


