// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerAnimInstance.h"
#include "../Player/Creature.h"
#include "../Player/MyPlayer.h"
#include "GameFramework/Character.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Animation/AnimInstance.h"
#include "Animation/AnimMontage.h"


UPlayerAnimInstance::UPlayerAnimInstance()
{


	static ConstructorHelpers::FObjectFinder<UAnimMontage> Knignt
	(TEXT("/Script/Engine.AnimMontage'/Game/Blueprint/Animation/Player/Knight_Montage.Knight_Montage'"));

	if (Knignt.Succeeded())
	{
		_myAnimMontage = Knignt.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> Guard
	(TEXT("/Script/Engine.AnimMontage'/Game/Blueprint/Animation/Player/Shield_Montage.Shield_Montage'"));
	if (Guard.Succeeded())
	{
		_shieldMontage = Guard.Object;
	}

	GuardLoopSectionName = TEXT("GuardLoop");
	GuardEndSectionName = TEXT("GuardEnd");
	GuardStartSectionName = TEXT("GuardStart");

	static ConstructorHelpers::FObjectFinder<UAnimMontage> HitReaction
	(TEXT("/Script/Engine.AnimMontage'/Game/Blueprint/Animation/Player/HitMotionMontage.HitMotionMontage'"));
	if (HitReaction.Succeeded())
	{
		HitReactionMontage = HitReaction.Object;
	}


	static ConstructorHelpers::FObjectFinder<UAnimMontage> Skill01Montage
	(TEXT("/Script/Engine.AnimMontage'/Game/Blueprint/Animation/Player/Skill_01_Mongtage.Skill_01_Mongtage'"));
	if (Skill01Montage.Succeeded())
	{
		_skill01Montage = Skill01Montage.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> Skill02Montage
	(TEXT("/Script/Engine.AnimMontage'/Game/Blueprint/Animation/Player/Skill_02_Mongtage.Skill_02_Mongtage'"));
	if (Skill02Montage.Succeeded())
	{
		_skill02Montage = Skill02Montage.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> Skill03Montage
	(TEXT("/Script/Engine.AnimMontage'/Game/Blueprint/Animation/Player/Skill_03_Montage.Skill_03_Montage'"));
	if (Skill03Montage.Succeeded())
	{
		_skill03Montage = Skill03Montage.Object;
	}



	static ConstructorHelpers::FObjectFinder<UAnimMontage> ChangeMontage
	(TEXT("/Script/Engine.AnimMontage'/Game/Blueprint/Animation/Player/ChangeDragonMontage.ChangeDragonMontage'"));
	if (ChangeMontage.Succeeded())
	{
		_changeMontage = ChangeMontage.Object;
	}


	
}

void UPlayerAnimInstance::PlayGuardMontage(bool bIsGuarding)
{
	if(bIsGuarding)
	{
		if (!Montage_IsPlaying(_shieldMontage))
		{
			// 방어 애니메이션 시작 (GuardStart 섹션)
			Montage_Play(_shieldMontage, 1.0f);
			Montage_JumpToSection(FName("GuardStart"), _shieldMontage);
		}
		// 방어 상태일 때 GuardLoop 섹션으로 이동 (루프)
		Montage_JumpToSection(FName("GuardLoop"), _shieldMontage);
	}
	else
	{
		// 방어가 해제될 때 GuardEnd 섹션으로 이동
		Montage_JumpToSection(FName("GuardEnd"), _shieldMontage);
	}

}


void UPlayerAnimInstance::StopGuardMontage()
{
	if (Montage_IsPlaying(_shieldMontage))
	{
		Montage_Stop(0.0f, _shieldMontage);
	}
}

void UPlayerAnimInstance::PlaySkill01Montage()
{
	if (_skill01Montage)
	{
		Montage_Play(_skill01Montage);
	}
}

void UPlayerAnimInstance::PlaySkill02Montage()
{
	if (_skill02Montage)
	{
		Montage_Play(_skill02Montage);
	}
}

void UPlayerAnimInstance::PlaySkill03Montage()
{
	if (_skill03Montage)
	{
		Montage_Play(_skill03Montage);
	}
}


void UPlayerAnimInstance::PlayChangeMontage()
{
	if (_changeMontage)
	{
		Montage_Play(_changeMontage);
	}
}

void UPlayerAnimInstance::AnimNotify_clickNext()
{
	_comboDelegate.Broadcast();
}

void UPlayerAnimInstance::AnimNotify_Attackhit()
{
	_attackDelegate.Broadcast();
}

void UPlayerAnimInstance::AnimNotify_Death()
{
	_deathDelegate_Knight.Broadcast();
}



