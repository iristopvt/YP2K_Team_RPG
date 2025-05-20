// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTService_LongFindTarget.generated.h"

/**
 * 
 */
UCLASS()
class PROTOTYPE_API UBTService_LongFindTarget : public UBTService
{
	GENERATED_BODY()
	
public:
	UBTService_LongFindTarget();
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

};
