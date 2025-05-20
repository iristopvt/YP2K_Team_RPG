// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/AI/BTDecorator_Stun.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController_BossMonster.h"
#include "../BossMonster.h"


UBTDecorator_Stun::UBTDecorator_Stun()
{
    NodeName = TEXT("Stun");
}

bool UBTDecorator_Stun::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const 
{
    bool result = Super::CalculateRawConditionValue(OwnerComp,NodeMemory);
    auto CurrentPawn = OwnerComp.GetAIOwner()->GetPawn();
    ABossMonster* boss = Cast<ABossMonster>(CurrentPawn);
    if(boss != nullptr)
    {
        return boss->GetIsStun();
    }

    return result;
}
