// Fill out your copyright notice in the Description page of Project Settings.

#include "Monster/AI/BTService_FindTarget.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController_NormalMonster.h"
#include "../Monster.h"
#include "../BossMonster.h"
#include "../Boss2Monster.h"
#include "../../Player/MyPlayer.h"
#include "DrawDebugHelpers.h"
#include "Engine/OverlapResult.h"

#include "../NormalMonster.h"
#include "Base/MyGameInstance.h"
#include "Base/Managers/SoundManager.h"
#include "Base/Managers/EffectManager.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"

UBTService_FindTarget::UBTService_FindTarget()
{
    NodeName = TEXT("FindTarget");
    Interval = 0.5f;
}

void UBTService_FindTarget::TickNode(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory, float DeltaSeconds)
{
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

    //몬스터
    auto currentPawn = OwnerComp.GetAIOwner()->GetPawn();
    if (currentPawn == nullptr)
    {
        UE_LOG(LogTemp, Warning, TEXT("NO currentPawn"));
        return;
    }
        

    auto world = GetWorld();
    FVector center = currentPawn->GetActorLocation();
    float searchRadius = 500.0f;

    ABossMonster* boss = Cast<ABossMonster>(currentPawn);
    ABoss2Monster* boss2 = Cast<ABoss2Monster>(currentPawn);
    if(boss!=nullptr || boss2 != nullptr)
    {
        searchRadius = 3000.f;
    }


    if (world == nullptr)
        return;

    TArray<FOverlapResult> overLapResult;
    FCollisionQueryParams qparams(NAME_None, false, currentPawn);

    bool bResult = world->OverlapMultiByChannel(
        overLapResult,
        center,
        FQuat::Identity,
        ECollisionChannel::ECC_GameTraceChannel2,
        FCollisionShape::MakeSphere(searchRadius),
        qparams);

    if (bResult)
    {
        for (auto &result : overLapResult)
        {   
            // target // 플레이어
            auto myCharacter = Cast<AMyPlayer>(result.GetActor());

            if (myCharacter != nullptr)
            {
                auto myCharacterController = myCharacter->GetController();
                if (myCharacterController != nullptr && myCharacterController->IsPlayerController())
                {
                    OwnerComp.GetBlackboardComponent()->SetValueAsObject(FName(TEXT("Target")), myCharacter);
                   // DrawDebugSphere(world, center, searchRadius, 32, FColor::Red, false, 0.3f);

                    ANormalMonster* NMonster = Cast<ANormalMonster>(currentPawn);
                    if (NMonster == nullptr)  return;
                    NMonster->PlayFindEffect();
                }

                return;
            }
        }
        OwnerComp.GetBlackboardComponent()->SetValueAsObject(FName(TEXT("Target")), nullptr);
       // DrawDebugSphere(world, center, searchRadius, 32, FColor::Green, false, 0.3f);
    }
  /*   else
     {
         OwnerComp.GetBlackboardComponent()->SetValueAsObject(FName(TEXT("Target")), nullptr);
         DrawDebugSphere(world, center, searchRadius, 32, FColor::Green, false, 0.3f);
     }*/
}

