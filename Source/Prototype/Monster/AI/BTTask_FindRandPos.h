// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_FindRandPos.generated.h"

/**
 * 
 */
UCLASS()
class PROTOTYPE_API UBTTask_FindRandPos : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTask_FindRandPos();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;	
};
