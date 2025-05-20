// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTaskNode_LookTarget.generated.h"

/**
 * 
 */
UCLASS()
class PROTOTYPE_API UBTTaskNode_LookTarget : public UBTTaskNode
{
    GENERATED_BODY()
public:
    UBTTaskNode_LookTarget();

protected:
    virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
    virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

private:
    FRotator TargetRotation;
    bool bIsRotating = false;

    
};

