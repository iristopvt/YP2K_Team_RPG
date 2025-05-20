// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/AI/BTTask_BossDash.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController_BossMonster.h"
#include "../BossMonster.h"


UBTTask_BossDash::UBTTask_BossDash()
{
    NodeName = TEXT("Dash");
    bNotifyTick = true; 
}

EBTNodeResult::Type UBTTask_BossDash::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    auto boss = Cast<ABossMonster>(OwnerComp.GetAIOwner()->GetPawn());
    if (boss == nullptr || boss->GetIsDashing()) 
        return EBTNodeResult::Failed;

    AActor *TargetActor = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject("Target"));
    if (TargetActor)
    {
        FVector TargetLocation = TargetActor->GetActorLocation();
        boss->Dash(TargetLocation);
        return EBTNodeResult::InProgress;
    }

    return EBTNodeResult::Failed;
}

void UBTTask_BossDash::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

    auto boss = Cast<ABossMonster>(OwnerComp.GetAIOwner()->GetPawn());
    if (boss && !boss->GetIsDashing())
    {
        FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
    }
}
