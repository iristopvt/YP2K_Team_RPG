// Fill out your copyright notice in the Description page of Project Settings.
#include "Monster/AI/BTService_CheckHP.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "AIController_BossMonster.h"
#include "../../Component/StatComponent.h"
#include "../BossMonster.h"
#include "Engine/OverlapResult.h"

UBTService_CheckHP::UBTService_CheckHP()
{
    NodeName = TEXT("Check HPPercent");
}

void UBTService_CheckHP::TickNode(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory, float DeltaSeconds)
{
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

    auto AIController = OwnerComp.GetAIOwner();

    if (AIController == nullptr)
        return;
        
    ABossMonster *boss = Cast<ABossMonster>(AIController->GetPawn());
    if (boss == nullptr || boss->_StatCom == nullptr)
    {
        UE_LOG(LogTemp, Warning, TEXT("Boss or StatComponent is missing."));
        return;
    }

    UStatComponent *stat = boss->_StatCom;
    float HealthPercentage = stat->HpRatio();
    
    OwnerComp.GetBlackboardComponent()->SetValueAsFloat("HpPersent", HealthPercentage);

}