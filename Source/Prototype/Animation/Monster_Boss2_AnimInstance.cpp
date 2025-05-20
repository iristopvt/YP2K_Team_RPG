// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/Monster_Boss2_AnimInstance.h"


UMonster_Boss2_AnimInstance::UMonster_Boss2_AnimInstance()
{
    static ConstructorHelpers::FObjectFinder<UAnimMontage> BM_01
	(TEXT("/Script/Engine.AnimMontage'/Game/Blueprint/Animation/Monster/BossMonster/Boss2/Boss2Attack_Montage.Boss2Attack_Montage'"));

	if (BM_01.Succeeded())
	{
		_myAnimMontage = BM_01.Object;
	}

	  static ConstructorHelpers::FObjectFinder<UAnimMontage> BM_02
	(TEXT("/Script/Engine.AnimMontage'/Game/Blueprint/Animation/Monster/BossMonster/Boss2/Boss2Skill_Montage.Boss2Skill_Montage'"));

	if (BM_02.Succeeded())
	{
		_skillMontage = BM_02.Object;
	}
   
}

void UMonster_Boss2_AnimInstance::PlaySkillMontage()
{
	if (!Montage_IsPlaying(_skillMontage))
	{
		Montage_Play(_skillMontage);
	}
}


void UMonster_Boss2_AnimInstance::AnimNotify_Attackhit()
{
    _attackDelegate.Broadcast();
}

void UMonster_Boss2_AnimInstance::AnimNotify_Death()
{
    _deathDelegate.Broadcast();
}

void UMonster_Boss2_AnimInstance::AnimNotify_Fire()
{	
	_skillDelegate.Broadcast(_targetLocation);
}