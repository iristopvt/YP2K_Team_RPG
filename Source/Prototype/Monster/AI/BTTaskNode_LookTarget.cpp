// Fill out your copyright notice in the Description page of Project Settings.

#include "Monster/AI/BTTaskNode_LookTarget.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "AIController_BossMonster.h"
#include "../BossMonster.h"
#include "../Monster.h"


UBTTaskNode_LookTarget::UBTTaskNode_LookTarget()
{
    bNotifyTick = true;
    NodeName = "LookTarget";
}

EBTNodeResult::Type UBTTaskNode_LookTarget::ExecuteTask(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory)
{
    auto CurrentPawn = OwnerComp.GetAIOwner()->GetPawn();
    AMonster *Boss = Cast<AMonster>(CurrentPawn);
    if (Boss == nullptr)
    {
        return EBTNodeResult::Failed;
    }

    if(Boss->GetIsAttacking())
    {
        return EBTNodeResult::Succeeded;
    }

    AActor *TargetActor = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject("Target"));
    if (TargetActor)
    {
        FVector TargetLocation = TargetActor->GetActorLocation();
        FVector Direction = TargetLocation - Boss->GetActorLocation();
        Direction.Z = 0.0f; 
        TargetRotation = FRotationMatrix::MakeFromX(Direction).Rotator();
    }

    bIsRotating = true;
    return EBTNodeResult::InProgress;
}

void UBTTaskNode_LookTarget::TickTask(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory, float DeltaSeconds)
{
    if (!bIsRotating)
    {
        FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
        return;
    }
    
    auto CurrentPawn = OwnerComp.GetAIOwner()->GetPawn();
    AMonster *Boss = Cast<AMonster>(CurrentPawn);
    if (Boss == nullptr)
    {
        return;
    }

    FRotator CurrentRotation = Boss->GetActorRotation();
    float InterpSpeed = 3.0f;

    FRotator NewRotation = FMath::RInterpTo(CurrentRotation, TargetRotation, DeltaSeconds, InterpSpeed);
    Boss->SetActorRotation(NewRotation);

    if (CurrentRotation.Equals(TargetRotation, 1.0f))
    {
        bIsRotating = false;
        FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
    }


}


