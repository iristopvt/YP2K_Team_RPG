// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AIController_BossMonster.generated.h"

/**
 * 
 */
UCLASS()
class PROTOTYPE_API AAIController_BossMonster : public AAIController
{
	GENERATED_BODY()
public:

	AAIController_BossMonster();

	virtual void OnPossess(APawn* InPawn) override;

	virtual void OnUnPossess() override;

	static const FName TargetKey;

	void RandMove();

private:
	UPROPERTY()
	class UBlackboardData* _bb;

	UPROPERTY()
	class UBehaviorTree* _bt;
	
	
};
