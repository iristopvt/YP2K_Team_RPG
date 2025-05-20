// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/BaseAnimInstance.h"
#include "Monster_Boss01_AnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class PROTOTYPE_API UMonster_Boss01_AnimInstance : public UBaseAnimInstance
{
	GENERATED_BODY()
	
public:
	UMonster_Boss01_AnimInstance();

	void PlayUpAttackMontage();

	virtual void JumpToSection(int32 sectionIndex) override;

	AttackDelegate _attackDelegate;

	DeathDelegate _deathDelegate;
	StunEndDelegate _stunDelegate;

	UFUNCTION()
	virtual void AnimNotify_Attackhit();

	UFUNCTION()
	virtual void AnimNotify_Death();

	UFUNCTION()
	virtual void AnimNotify_StunEnd();

	//UFUNCTION()
	//virtual void AnimNotify_StunEnd();

private:
	//어퍼컷
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player", Meta = (AllowPrivateAccess = true))
	class UAnimMontage* _myUpAttackMontage;


};
