// Fill out your copyright notice in the Description page of Project Settings.

#include "Player/Creature.h"
#include "Engine/DamageEvents.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "DrawDebugHelpers.h"

#include "Component/StatComponent.h"
#include "Base/MyGameInstance.h"

#include "../Animation/BaseAnimInstance.h"
#include "../Base/Managers/SoundManager.h"
#include "../Player/MyPlayer.h"
#include "../Player/Dragon.h"

// Sets default values
ACreature::ACreature()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bIsGuarding = false;
	// cheol
	_StatCom = CreateDefaultSubobject<UStatComponent>(TEXT("StatCom"));

	_isTransformed = false;
}

// Called when the game starts or when spawned
void ACreature::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ACreature::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACreature::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void ACreature::Init()
{
}

void ACreature::Disable()
{
}

void ACreature::AttackHit()
{
	TArray<FHitResult> hitResults;
	FCollisionQueryParams params(NAME_None, false, this);

	float attackRange = _StatCom->GetAttackRange();
	float attackRadius = _StatCom->GetAttackRadius();

	FVector capsuleCenter = GetActorLocation() + GetActorForwardVector() * (attackRange * 0.5f);

	FQuat capsuleRotation = FQuat::FindBetweenNormals(FVector::UpVector, GetActorForwardVector());

	bool bResult = GetWorld()->SweepMultiByChannel(
		hitResults,
		capsuleCenter,
		capsuleCenter,
		capsuleRotation,
		ECollisionChannel::ECC_GameTraceChannel2,
		FCollisionShape::MakeCapsule(attackRadius, attackRange * 0.5f),
		params);

	FColor drawColor = FColor::Green;

	if (bResult)
	{
		drawColor = FColor::Red;

		for (auto &hitResult : hitResults)
		{
			if (hitResult.GetActor() && hitResult.GetActor()->IsValidLowLevel())
			{
				FDamageEvent DamageEvent;
				hitResult.GetActor()->TakeDamage(_StatCom->GetStr(), DamageEvent, GetController(), this);

				_hitPoint = hitResult.ImpactPoint;
				SoundManager->PlaySound(*GetHitSoundName(), _hitPoint);
				EffectManager->Play(*GetPlayerAttackHitEffect(), _hitPoint);
				break;
			}
		}
	}
	else
	{
		FVector missLocation = GetActorLocation();

		SoundManager->PlaySound(*GetSwingSoundName(), missLocation);
	}

	/*DrawDebugCapsule(
		GetWorld(),
		capsuleCenter,
		attackRange * 0.5f,
		attackRadius,
		capsuleRotation,
		drawColor,
		false,
		0.3f);*/
}

FString ACreature::GetHitSoundName() const
{
	return "default_hit_sound";
}

FString ACreature::GetSwingSoundName() const
{
	return "default_SwingAttackSound";
}

FString ACreature::GetGuardOn() const
{
	return "default_ShieldSound";
}

FString ACreature::GetGuardOff() const
{
	return "default_ShieldSound";
}

FString ACreature::GetDeadSoundName() const
{
	return "default_DeadSound";
}

FString ACreature::GetSkillSound01() const
{
	return "default_Skill01";
}

FString ACreature::GetSkillSound02() const
{
	return "default_Skill02";
}

FString ACreature::GetSkillSound03() const
{
	return "default_Skill03";
}

FString ACreature::GetSkillSound03Shout() const
{
	return "default_Skill03_Shout";
}

FString ACreature::GetSkillSound04Start() const
{
	return "default_Skill04_Start";
}

FString ACreature::GetSkillSound04Durring() const
{
	return "default_Skill04_Durring";
}

FString ACreature::GetBossMonsterAttack() const
{
	return "default_BossMonsterAttack";
}

FString ACreature::GetSkillParticleEffect02() const
{
	return "default_Skill02_Effect";
}

FString ACreature::GetPlayerAttackHitEffect() const
{
	return "default_AttackHit_Effect";
}

FString ACreature::GetEpicAttackFarSound() const
{
	return "default_Sound";
}

FString ACreature::GetEpicAttackMagicDotSound() const
{
	return "default_Sound";
}

FString ACreature::GetPlayerSkillEffect04_Start() const
{
	return "default_Start";
}

FString ACreature::GetPlayerSkillEffect04_Durring() const
{
	return "default_Durring";
}

FString ACreature::GetUIBaseSound() const
{
	return "default_Sound";
}

FString ACreature::GetEpicSkeletonEffect() const
{
	return "default_Effect";
}

FString ACreature::GetEpicSpawnSound() const
{
	return "default_Spawn";
}

FString ACreature::GetLevelUpSound() const
{
	return "default_LevelUpSound";
}

void ACreature::OnAttackEnded(UAnimMontage *Montage, bool bInterrupted)
{
	_isAttacking = false;
	_attackEndedDelegate.Broadcast();
}

float ACreature::TakeDamage(float Damage, struct FDamageEvent const &DamageEvent, AController *EventInstigator, AActor *DamageCauser)
{
	Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);

	FVector AttackDirection = DamageCauser->GetActorLocation() - GetActorLocation();
	AttackDirection.Z = 0.0f;
	AttackDirection.Normalize();

	FVector GuardDirection = GetActorForwardVector();

	float DotProduct = FVector::DotProduct(GuardDirection, AttackDirection);
	float Angle = FMath::Acos(DotProduct) * (180.0f / PI);

	const float GuardAngle = 90.0f;

	if (bIsGuarding && Angle <= GuardAngle)
	{
		SoundManager->PlaySound(*GetGuardOn(), _hitPoint);
	}
	else
	{
		UBaseAnimInstance *AnimInstance = Cast<UBaseAnimInstance>(GetMesh()->GetAnimInstance());
		if (AnimInstance)
		{
			AnimInstance->PlayHitReactionMontage();
		}

		SoundManager->PlaySound(*GetGuardOff(), _hitPoint);

		FVector KnockbackDirection = GetActorLocation() - DamageCauser->GetActorLocation();
		KnockbackDirection.Z = 0.0f;
		KnockbackDirection.Normalize();
		LaunchCharacter(KnockbackDirection * 1000.f, true, true);
		_StatCom->AddCurHp(-Damage);

		if (_StatCom->IsDead())
		{
			SoundManager->PlaySound(*GetDeadSoundName(), this->GetActorLocation());

			SetActorEnableCollision(false);
			auto controller = GetController();
			if (controller)
				GetController()->UnPossess();

			GetWorld()->GetTimerManager().SetTimer(TimerHandle_Destroy, this, &ACreature::DelayedDestroy, 2.0f, false);
		}
	}

	return 0.0f;
}

void ACreature::DelayedDestroy()
{
	Destroy();
}
