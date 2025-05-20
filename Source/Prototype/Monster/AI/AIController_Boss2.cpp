// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/AI/AIController_Boss2.h"
#include "NavigationSystem.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"


AAIController_Boss2::AAIController_Boss2()
{
    static ConstructorHelpers::FObjectFinder<UBlackboardData> BB(TEXT("/Script/AIModule.BlackboardData'/Game/Blueprint/AI/Boss2_BB.Boss2_BB'"));
	{
		_bb = BB.Object;
	}

	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BT(TEXT("/Script/AIModule.BehaviorTree'/Game/Blueprint/AI/Boss2_BT.Boss2_BT'"));
	{
		_bt = BT.Object;
	}
}

void AAIController_Boss2::OnPossess(APawn* InPawn)
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

void AAIController_Boss2::OnUnPossess()
{
    Super::OnUnPossess();
}
