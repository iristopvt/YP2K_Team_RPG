// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/AI/BTTaskNode_FlyAttack.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Monster/AI/AIController_Epic.h"
#include "Monster/EpicMonster_witch.h"

UBTTaskNode_FlyAttack::UBTTaskNode_FlyAttack()
{
	NodeName = TEXT("Attack");

}

EBTNodeResult::Type UBTTaskNode_FlyAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type result = Super::ExecuteTask(OwnerComp, NodeMemory);
	//auto character = Cast<AEpicMonster>(OwnerComp.GetAIOwner()->GetPawn());
	auto character = Cast<AEpicMonster_witch>(OwnerComp.GetAIOwner()->GetPawn());

	if (character == nullptr)
		return EBTNodeResult::Failed;

	character->Attack_AI();
	//character->MeleeAttackhit();

	_isAttacking = true;


	return result;
}

void UBTTaskNode_FlyAttack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	if (_isAttacking == false)
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
}
