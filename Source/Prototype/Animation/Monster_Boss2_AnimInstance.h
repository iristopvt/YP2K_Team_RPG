// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/BaseAnimInstance.h"
#include "Monster_Boss2_AnimInstance.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSkillDelegate, FVector, Location);

/**
 * 
 */
UCLASS()
class PROTOTYPE_API UMonster_Boss2_AnimInstance : public UBaseAnimInstance
{
	GENERATED_BODY()
public:
	UMonster_Boss2_AnimInstance();

	virtual void PlaySkillMontage();

	AttackDelegate _attackDelegate;
	DeathDelegate _deathDelegate;
	
	FSkillDelegate _skillDelegate;

	FVector GetTarget(){return _targetLocation;}
	void SetTarget(FVector location){_targetLocation = location;}

	UFUNCTION()
	virtual void AnimNotify_Attackhit();

	UFUNCTION()
	virtual void AnimNotify_Death();

	UFUNCTION()
	virtual void AnimNotify_Fire();

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill", Meta = (AllowPrivateAccess = true))
	class UAnimMontage* _skillMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Target", Meta = (AllowPrivateAccess = true))
	FVector _targetLocation;

	
};
