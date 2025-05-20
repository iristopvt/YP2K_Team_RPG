// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/AI/BTDecorator_CanAttack.h"

#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController_BossMonster.h"
#include "../../Player/MyPlayer.h"


UBTDecorator_CanAttack::UBTDecorator_CanAttack()
{
    NodeName = TEXT("CanAttack");
}

bool UBTDecorator_CanAttack::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const 
{
    bool result = Super::CalculateRawConditionValue(OwnerComp,NodeMemory);

    auto CurrentPawn = OwnerComp.GetAIOwner()->GetPawn();
    auto Target = Cast<AMyPlayer>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(FName(TEXT("Target"))));

    if(CurrentPawn == nullptr || Target == nullptr)
        return false;

    float Distance = Target->GetDistanceTo(CurrentPawn);

   /* return Distance < 700.0f;

    return result;*/
    return Distance < 700.0f && result;  // 두 조건을 동시에 만족해야만 true를 반환하도록 수정
}
