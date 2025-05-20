// Fill out your copyright notice in the Description page of Project Settings.

#include "Monster/AI/BTService_PlayerDistance.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "AIController_BossMonster.h"
#include "../Monster.h"
#include "../../Player/MyPlayer.h"
#include "DrawDebugHelpers.h"
#include "Engine/OverlapResult.h"

UBTService_PlayerDistance::UBTService_PlayerDistance()
{
    NodeName = TEXT("Check PlayerDistance");
}

void UBTService_PlayerDistance::TickNode(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory, float DeltaSeconds)
{
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

    auto AIController = OwnerComp.GetAIOwner();
    if (!AIController)
        return;

    auto ControlledPawn = Cast<AMonster>(AIController->GetPawn());
    auto PlayerActor = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

    if (ControlledPawn && PlayerActor)
    {
        float Distance = FVector::Dist(ControlledPawn->GetActorLocation(), PlayerActor->GetActorLocation());
        OwnerComp.GetBlackboardComponent()->SetValueAsFloat("Distance",Distance);

        if (Distance < 300.0f)
        {
            OwnerComp.GetBlackboardComponent()->SetValueAsBool("ChaseTarget",true);
        }
        else
        {
            OwnerComp.GetBlackboardComponent()->SetValueAsBool("ChaseTarget",false);
        }
    }
}
