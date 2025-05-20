// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/AI/BTTask_Attack.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController_NormalMonster.h"
#include "../Monster.h"


UBTTask_Attack::UBTTask_Attack()
{
    NodeName = TEXT("Attack");
}

EBTNodeResult::Type UBTTask_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp,uint8* NodeMemory)
{
    EBTNodeResult::Type result = Super::ExecuteTask(OwnerComp,NodeMemory);

    auto monster = Cast<AMonster>(OwnerComp.GetAIOwner()->GetPawn());
    if(monster == nullptr)
        return EBTNodeResult::Failed;

    monster->Attack_AI();

    // character->_attackEndedDelegate.AddLambda(
	// 	[this]() -> void
	// 	{
	// 		this->_isAttacking = false;
	// 	});

    return result;
}

void UBTTask_Attack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory,float DeltaSeconds)
{
    Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	if (_isAttacking == false)
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
}
