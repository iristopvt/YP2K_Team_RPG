// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/AI/AIController_Epic.h"
#include "NavigationSystem.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"

//const FName AAIController_Epic::TargetKey(TEXT("Target"));


AAIController_Epic::AAIController_Epic()
{
	static ConstructorHelpers::FObjectFinder<UBlackboardData> BB(TEXT("/Script/AIModule.BlackboardData'/Game/Blueprint/AI/EpicMonster_BB.EpicMonster_BB'"));
	{
		_bb = BB.Object;
	}

	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BT(TEXT("/Script/AIModule.BehaviorTree'/Game/Blueprint/AI/EpicMonster_BT.EpicMonster_BT'"));
	{
		_bt = BT.Object;
	}
}

void AAIController_Epic::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	UBlackboardComponent* blackBoarComponent = Blackboard;
	if (UseBlackboard(_bb, blackBoarComponent))
	{
		if (RunBehaviorTree(_bt))
		{
			blackBoarComponent->SetValueAsVector(FName(TEXT("FixedPos")), InPawn->GetActorLocation());
		}
	}
}

void AAIController_Epic::OnUnPossess()
{
	Super::OnUnPossess();

}

void AAIController_Epic::RandMove()
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
