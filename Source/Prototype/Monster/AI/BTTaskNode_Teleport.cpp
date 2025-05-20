// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/AI/BTTaskNode_Teleport.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Monster/AI/AIController_Boss2.h"
#include "Monster/Boss2Monster.h"


UBTTaskNode_Teleport::UBTTaskNode_Teleport()
{
     NodeName = TEXT("Teleport");
}


EBTNodeResult::Type UBTTaskNode_Teleport::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
     EBTNodeResult::Type result = Super::ExecuteTask(OwnerComp, NodeMemory);
	auto boss = Cast<ABoss2Monster>(OwnerComp.GetAIOwner()->GetPawn());

	if (boss == nullptr)
		return EBTNodeResult::Failed;

    AActor *TargetActor = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject("Target"));
    if (TargetActor)
    {
        FVector TargetLocation = TargetActor->GetActorLocation();
        boss->Teleport(TargetLocation);
    }

	return result;
}

void UBTTaskNode_Teleport::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    if (_isAttacking == false)
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
}


