// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTDecorator_Stun.generated.h"

/**
 * 
 */
UCLASS()
class PROTOTYPE_API UBTDecorator_Stun : public UBTDecorator
{
	GENERATED_BODY()

public:
	UBTDecorator_Stun();
	
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
