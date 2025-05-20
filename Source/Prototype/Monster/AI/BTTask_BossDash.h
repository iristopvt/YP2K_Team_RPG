// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_BossDash.generated.h"

/**
 * 
 */
UCLASS()
class PROTOTYPE_API UBTTask_BossDash : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTask_BossDash();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp,uint8* NodeMemory)override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory,float DeltaSeconds)override;

private:
	bool _isDashing = false;
};
