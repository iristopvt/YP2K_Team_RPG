// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/BaseAnimInstance.h"

#include "KismetAnimationLibrary.h"
#include "../Player/Creature.h"
#include "../Player/MyPlayer.h"
#include "../Player/Dragon.h"
#include "GameFramework/PawnMovementComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

UBaseAnimInstance::UBaseAnimInstance()
{
	_isFalling = false;
	_isDead = false;

	_speed = 0.0f;
	_Direction = 0;
	_vertical = 0;
	_horizontal = 0;
}

void UBaseAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	ACreature* myCharacter = Cast<ACreature>(TryGetPawnOwner());

	if (myCharacter != nullptr)
	{
		_speed = myCharacter->GetVelocity().Size();

		if(ADragon* Dragon = Cast<ADragon>(myCharacter))
		{
			if (Dragon->GetCharacterMovement()->IsFalling())
			{
				// 점프 상태에서의 비행 속도 동기화
				Dragon->GetCharacterMovement()->MaxFlySpeed = _speed;
			}
			else
			{
				// 지상에서는 MaxSpeed를 기존 값으로 설정
				Dragon->GetCharacterMovement()->MaxFlySpeed = 600.0f; // 기본 속도
			}
		}





		_isFalling = myCharacter->GetMovementComponent()->IsFalling();
		_Direction = UKismetAnimationLibrary::CalculateDirection(myCharacter->GetVelocity(), myCharacter->GetActorRotation());

		_vertical = _speed + (myCharacter->GetVertical() - _speed) * (DeltaSeconds);
		_horizontal = _Direction + (myCharacter->GetHorizontal() - _Direction) * (DeltaSeconds);
		_isDead = (myCharacter->GetCurHp() <= 0);

		_vertical = _vertical + (myCharacter->GetVertical() - _vertical) * (DeltaSeconds);

	}

	//추가시도...
	APawn* OwningPawn = TryGetPawnOwner();
	if (OwningPawn && OwningPawn->GetMovementComponent())
	{
		_isFalling = OwningPawn->GetMovementComponent()->IsFalling();
	}

}

void UBaseAnimInstance::JumpToSection(int32 sectionIndex)
{
	FName sectionName = FName(*FString::Printf(TEXT("Attack%d"), sectionIndex));
	Montage_JumpToSection(sectionName);
}

void UBaseAnimInstance::PlayAttackMontage()
{
	//Montage_IsActive(_myAnimMontage);

	if ( !Montage_IsPlaying(_myAnimMontage))
	{
	
			Montage_Play(_myAnimMontage);

	}

}

void UBaseAnimInstance::PlayStunMontage()
{
	if (!Montage_IsPlaying(_myStunMontage))
	{
		Montage_Play(_myStunMontage);
	}
}

void UBaseAnimInstance::PlayDashMontage()
{
	if (!Montage_IsPlaying(_myDashingMontage))
	{
		Montage_Play(_myDashingMontage);
	}
}

void UBaseAnimInstance::PlayAttackFarMontage()
{
	if (!Montage_IsPlaying(_attackFarMontage))
	{
		Montage_Play(_attackFarMontage);
	}
}

void UBaseAnimInstance::PlayAttackDotrMontage()
{
	if (!Montage_IsPlaying(_attackMagicMontage))
	{
		Montage_Play(_attackMagicMontage);
	}
}

void UBaseAnimInstance::PlayHitReactionMontage()
{
	if (HitReactionMontage)
	{
		Montage_Play(HitReactionMontage);
	}
}



