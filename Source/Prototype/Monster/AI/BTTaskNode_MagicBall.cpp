// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/AI/BTTaskNode_MagicBall.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Monster/AI/AIController_Epic.h"
#include "Monster/EpicMonster_witch.h"



UBTTaskNode_MagicBall::UBTTaskNode_MagicBall()
{
	NodeName = TEXT("MagicBall");
}

EBTNodeResult::Type UBTTaskNode_MagicBall::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type result = Super::ExecuteTask(OwnerComp, NodeMemory);
	auto character = Cast<AEpicMonster_witch>(OwnerComp.GetAIOwner()->GetPawn());

	if (character == nullptr)
		return EBTNodeResult::Failed;
	
		character->MagicShot();
		count++;

		if (count == 3)
		{
			character->testDecalSkill();
			count = 0;
		}
		

	_isAttacking = true;


	return result;
}

void UBTTaskNode_MagicBall::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	if (_isAttacking == false)
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
}
