// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/AI/BTService_LongFindTarget.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController_NormalMonster.h"
#include "../Monster.h"
#include "../../Player/MyPlayer.h"
#include "DrawDebugHelpers.h"
#include "Engine/OverlapResult.h"

UBTService_LongFindTarget::UBTService_LongFindTarget()
{
	NodeName = TEXT("LongFindTarget");
	Interval = 0.5;
}

void UBTService_LongFindTarget::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);


    auto currentPawn = OwnerComp.GetAIOwner()->GetPawn();
    if (currentPawn == nullptr)
        return;

    auto world = GetWorld();
    FVector center = currentPawn->GetActorLocation();
    float searchRadius = 1000.0f;

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
        for (auto& result : overLapResult)
        {
            auto myCharacter = Cast<AMyPlayer>(result.GetActor());

            if (myCharacter != nullptr)
            {
                auto myCharacterController = myCharacter->GetController();
                if (myCharacterController != nullptr && myCharacterController->IsPlayerController())
                {
                    OwnerComp.GetBlackboardComponent()->SetValueAsObject(FName(TEXT("LongTarget")), myCharacter);
                    //DrawDebugSphere(world, center, searchRadius, 32, FColor::Red, false, 0.3f);
                }

                return;
            }
        }
        OwnerComp.GetBlackboardComponent()->SetValueAsObject(FName(TEXT("LongTarget")), nullptr);
        //DrawDebugSphere(world, center, searchRadius, 32, FColor::Green, false, 0.3f);
    }
   /* else
    {
        OwnerComp.GetBlackboardComponent()->SetValueAsObject(FName(TEXT("Target")), nullptr);
        DrawDebugSphere(world, center, searchRadius, 32, FColor::Green, false, 0.3f);
    }*/
}
