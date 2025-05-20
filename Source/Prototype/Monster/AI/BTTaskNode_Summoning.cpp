// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/AI/BTTaskNode_Summoning.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Monster/AI/AIController_Epic.h"
#include "Monster/EpicMonster_witch.h"

UBTTaskNode_Summoning::UBTTaskNode_Summoning()
{
	NodeName = TEXT("Summoning");
}

EBTNodeResult::Type UBTTaskNode_Summoning::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type result = Super::ExecuteTask(OwnerComp, NodeMemory);
	auto character = Cast<AEpicMonster_witch>(OwnerComp.GetAIOwner()->GetPawn());

	if (character == nullptr)
		return EBTNodeResult::Failed;

	if (_SuMonster == false)
	{
		character->SumonedMonster();
	}

	_SuMonster = true;
	//_isAttacking = true;
	
	//character->SumonedMonster();


	_isAttacking = true;


	return result;
}

void UBTTaskNode_Summoning::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	if (_isAttacking == false)
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
}
