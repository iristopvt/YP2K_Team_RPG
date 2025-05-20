// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTaskNode_Teleport.generated.h"

/**
 * 
 */
UCLASS()
class PROTOTYPE_API UBTTaskNode_Teleport : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UBTTaskNode_Teleport();
	
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

private:
	bool _isAttacking = false;
	
};
