// Fill out your copyright notice in the Description page of Project Settings.

#include "Monster/AI/AIController_BossMonster.h"
#include "NavigationSystem.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"

AAIController_BossMonster::AAIController_BossMonster()
{
    static ConstructorHelpers::FObjectFinder<UBlackboardData> BB(TEXT("/Script/AIModule.BlackboardData'/Game/Blueprint/AI/BossMonster_BB.BossMonster_BB'"));
    {
        _bb = BB.Object;
    }

    static ConstructorHelpers::FObjectFinder<UBehaviorTree> BT(TEXT("/Script/AIModule.BehaviorTree'/Game/Blueprint/AI/BossMonster_BT.BossMonster_BT'"));
    {
        _bt = BT.Object;
    }
}

void AAIController_BossMonster::OnPossess(APawn *InPawn)
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

void AAIController_BossMonster::OnUnPossess()
{
    Super::OnUnPossess();
}

void AAIController_BossMonster::RandMove()
{
}
