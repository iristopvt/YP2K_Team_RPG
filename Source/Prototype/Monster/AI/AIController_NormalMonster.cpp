// Fill out your copyright notice in the Description page of Project Settings.

#include "Monster/AI/AIController_NormalMonster.h"
#include "NavigationSystem.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"

const FName AAIController_NormalMonster::TargetKey(TEXT("Target"));

AAIController_NormalMonster::AAIController_NormalMonster()
{
    static ConstructorHelpers::FObjectFinder<UBlackboardData> BB(TEXT("/Script/AIModule.BlackboardData'/Game/Blueprint/AI/NormalMonster_BB.NormalMonster_BB'"));
    {
        _bb = BB.Object;
    }

    static ConstructorHelpers::FObjectFinder<UBehaviorTree> BT(TEXT("/Script/AIModule.BehaviorTree'/Game/Blueprint/AI/NormalMonster_BT.NormalMonster_BT'"));
    {
        _bt = BT.Object;
    }
}

void AAIController_NormalMonster::OnPossess(APawn *InPawn)
{
    Super::OnPossess(InPawn);

    UBlackboardComponent *blackboardComponent = Blackboard;
    if (UseBlackboard(_bb, blackboardComponent))
    {
        if (RunBehaviorTree(_bt))
        {
            blackboardComponent->SetValueAsVector(FName(TEXT("FixedPos")),InPawn->GetActorLocation());
        }
    }
}

void AAIController_NormalMonster::OnUnPossess()
{
    Super::OnUnPossess();
}

void AAIController_NormalMonster::RandMove()
{
    auto currentPawn = GetPawn();

    if (!currentPawn->IsValidLowLevel())
        return;

    UNavigationSystemV1* NaviSystem = UNavigationSystemV1::GetNavigationSystem(GetWorld());
    if (NaviSystem == nullptr)
        return;

    FNavLocation randLocation;

    if (NaviSystem->GetRandomPointInNavigableRadius(currentPawn->GetActorLocation(), 500.f, randLocation))
    {
        UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, randLocation);
    }
}
