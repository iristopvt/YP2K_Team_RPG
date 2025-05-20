// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTaskNode_MagicBall.generated.h"

/**
 * 
 */
UCLASS()
class PROTOTYPE_API UBTTaskNode_MagicBall : public UBTTaskNode
{
	GENERATED_BODY()

public:

	UBTTaskNode_MagicBall();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

private:
	bool _isAttacking = false;
	int count = 0;
	
};
