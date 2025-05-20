// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AIController_Boss2.generated.h"

/**
 * 
 */
UCLASS()
class PROTOTYPE_API AAIController_Boss2 : public AAIController
{
	GENERATED_BODY()
public:
	AAIController_Boss2();

	virtual void OnPossess(APawn* InPawn) override;

	virtual void OnUnPossess() override;

	static const FName TargetKey;

private:
	UPROPERTY()
	class UBlackboardData* _bb;

	UPROPERTY()
	class UBehaviorTree* _bt;
	
};
