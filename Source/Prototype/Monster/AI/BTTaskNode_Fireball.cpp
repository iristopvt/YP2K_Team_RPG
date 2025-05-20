// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/AI/BTTaskNode_Fireball.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Monster/AI/AIController_Boss2.h"
#include "Monster/Boss2Monster.h"


UBTTaskNode_Fireball::UBTTaskNode_Fireball()
{
    NodeName = TEXT("Fire");
     bNotifyTick = true; 
}

EBTNodeResult::Type UBTTaskNode_Fireball::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    EBTNodeResult::Type result = Super::ExecuteTask(OwnerComp, NodeMemory);
	auto boss = Cast<ABoss2Monster>(OwnerComp.GetAIOwner()->GetPawn());

	if (boss == nullptr)
		return EBTNodeResult::Failed;

    AActor *TargetActor = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject("Target"));
    if (TargetActor)
    {
        FVector TargetLocation = TargetActor->GetActorLocation();
        boss->Skill_AI(TargetLocation);
        return EBTNodeResult::InProgress;
    }

	return result;
}

void UBTTaskNode_Fireball::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	 auto boss = Cast<ABoss2Monster>(OwnerComp.GetAIOwner()->GetPawn());
    if (boss && !boss->GetIsfire())
    {
        FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
    }
}
