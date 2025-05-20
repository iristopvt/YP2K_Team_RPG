// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/AI/BTTask_FindRandPos.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"

UBTTask_FindRandPos::UBTTask_FindRandPos()
{
    NodeName = TEXT("FindRandPos");
}

EBTNodeResult::Type UBTTask_FindRandPos::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    EBTNodeResult::Type result = Super::ExecuteTask(OwnerComp, NodeMemory);

    auto CurrentPawn = OwnerComp.GetAIOwner()->GetPawn();

    if(!CurrentPawn->IsValidLowLevel())
        return EBTNodeResult::Type::Failed;

    UNavigationSystemV1* NaviSystem = UNavigationSystemV1::GetNavigationSystem(GetWorld());
    if(NaviSystem == nullptr)
        return EBTNodeResult::Type::Failed;

    FNavLocation RandLocation;

    FVector FixedPos = OwnerComp.GetBlackboardComponent()->GetValueAsVector(FName(TEXT("FixedPos")));

    if(NaviSystem->GetRandomPointInNavigableRadius(FixedPos,500.0f,RandLocation))
    {
        OwnerComp.GetBlackboardComponent()->SetValueAsVector(FName(TEXT("RandPos")), RandLocation);
		return EBTNodeResult::Type::Succeeded;
    }

    return result;

}
