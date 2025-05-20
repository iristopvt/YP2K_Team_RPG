// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/EpicMonster_witch.h"
#include "Base/MyGameInstance.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "../Player/Creature.h"
#include "Monster/AI/AIController_Epic.h"
#include "Engine/DamageEvents.h"
#include "EpicProjectile.h"
#include "NormalMonster.h"
#include "../Animation/Monster_N_AnimInstance.h"
#include "Monster/AI/AIController_NormalMonster.h"

#include "Monster/MagicDecal.h"

#include "Animation/Monster_Epic01_Anim.h"


AEpicMonster_witch::AEpicMonster_witch()
{
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> witch
	(TEXT("/Script/Engine.SkeletalMesh'/Game/ParagonMorigesh/Characters/Heroes/Morigesh/Meshes/Morigesh.Morigesh'"));

	if (witch.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(witch.Object);
	}

	static ConstructorHelpers::FClassFinder<AMagicDecal> Wide
	(TEXT("/Script/Engine.Blueprint'/Game/Blueprint/VFX/MagicDecal_BP.MagicDecal_BP_C''"));

	if (Wide.Succeeded())
	{
		_tedecal = Wide.Class;
	}



	_exp = 170;

	AIControllerClass = AAIController_Epic::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

void AEpicMonster_witch::BeginPlay()
{
	Super::BeginPlay();

}

void AEpicMonster_witch::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	if (_StatCom)
	{
		_StatCom->SetEpicLevelInit(1);
	}

	_monster_Epic_AnimInstance = Cast<UMonster_Epic01_Anim>(GetMesh()->GetAnimInstance());
	if (_monster_Epic_AnimInstance->IsValidLowLevelFast())
	{
		_monster_Epic_AnimInstance->OnMontageEnded.AddDynamic(this, &ACreature::OnAttackEnded);
		_monster_Epic_AnimInstance->_attackDelegate.AddUObject(this, &ACreature::AttackHit);
		_monster_Epic_AnimInstance->_death_Epic_MonsterDelegate.AddUObject(this, &AMonster::Disable);

	}
}

void AEpicMonster_witch::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEpicMonster_witch::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


void AEpicMonster_witch::MeleeAttackhit()
{
	FHitResult hitResult;
	FCollisionQueryParams params(NAME_None, false, this);

	float attackRange = 500.0f;
	float attackRadius = 150.0f;

	bool bResult = GetWorld()->SweepSingleByChannel
	(
		hitResult,
		GetActorLocation(),
		GetActorLocation() + GetActorForwardVector() * attackRange,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel2,
		FCollisionShape::MakeSphere(attackRadius),
		params
	);

	FVector vec = GetActorForwardVector() * attackRange;
	FVector center = GetActorLocation() + vec * 0.5f;

	FColor drawColor = FColor::Green;


	if (bResult && hitResult.GetActor()->IsValidLowLevel())
	{
		drawColor = FColor::Red;

		FDamageEvent DamageEvent;
		//hitResult.GetActor()->TakeDamage(_statCom->GetAttackDamage(), DamageEvent, GetController(), this);

	}

	DrawDebugSphere(GetWorld(), center, attackRadius, 12, drawColor, false, 2.0f);
}

void AEpicMonster_witch::Attack_AI()
{

	if (_isAttacking == false && _monster_Epic_AnimInstance != nullptr)
	{
		_monster_Epic_AnimInstance->PlayAttackMontage();
		_isAttacking = true;

		_curAttackIndex %= 2;
		_curAttackIndex++;

		_monster_Epic_AnimInstance->JumpToSection(_curAttackIndex);
	}

	
}

FString AEpicMonster_witch::GetEpicAttackFarSound() const
{
	return "EpicMonsterAttack_Far_Cue";
}

FString AEpicMonster_witch::GetEpicAttackMagicDotSound() const
{
	return "EpicMonsterAttack_MagicDot_Cue";
}

FString AEpicMonster_witch::GetDeadSoundName() const
{
	return "Morigesh_Effort_Death_Cue";
}

FString AEpicMonster_witch::GetEpicSkeletonEffect() const
{
	return "P_Morigesh_Ultimate_Reveal";
}

FString AEpicMonster_witch::GetEpicSpawnSound() const
{
	return "SpawnSound_Cue";
}



void AEpicMonster_witch::MagicShot()
{
	
		if (_projectileClass)
		{
			_monster_Epic_AnimInstance->PlayAttackFarMontage();
			_curAttackIndex = 1;

			FVector forward = GetActorForwardVector();
			FName HandSocketName = TEXT("Magic_hand");
		

			FVector fireLocation = GetMesh()->GetSocketLocation(HandSocketName);

			FRotator fireRotation = forward.Rotation();

			auto projectile = GetWorld()->SpawnActor<AEpicProjectile>(_projectileClass, fireLocation, fireRotation);
			if (projectile)
			{
				projectile->WitchMa(this);
				projectile->SetDamage(_StatCom->GetInt()); // 데미지 추후 수정 
				projectile->FireInDirection(forward);
				UE_LOG(LogTemp, Error, TEXT("MagicShot"));
			}
			
			
			SoundManager->PlaySound(*GetEpicAttackFarSound(),projectile->GetActorLocation());
		}

}

void AEpicMonster_witch::SumonedMonster()
{
	if (_SumonedMonster != nullptr)
	{

		for (int i = 0; i <= 4; ++i)
		{
			FVector SpawLocation = GetActorLocation() + FMath::VRand() * 200.0f;
			FRotator SpawRotation = FRotator::ZeroRotator;

			ANormalMonster* Noram = GetWorld()->SpawnActor<ANormalMonster>(_SumonedMonster, SpawLocation, SpawRotation);

			if (Noram)
			{
				USkeletalMeshComponent* MeshComponent = Noram->GetMesh();  
				if (MeshComponent)
				{
				/*	FName SocketName = FName("head");
					EffectManager->PlayOnSkeletalMesh(*GetEpicSkeletonEffect(), MeshComponent, SocketName);
					SoundManager->PlaySound(*GetEpicSpawnSound(), GetActorLocation());*/
				}
				Noram->SpawnDefaultController();
			}

			
		}
	}
}

void AEpicMonster_witch::testDecalSkill()
{

	if (_tedecal)
	{
		FVector forward = GetActorForwardVector();
		FVector fireLocation = GetActorLocation() + (forward * 150);
		fireLocation.Z -= 90.0f;
		FRotator fireRotation = forward.Rotation();

		float randFloat = FMath::FRandRange(0, PI * 2.0f);
		float X = cosf(randFloat) * 600.0f;
		float Y = sinf(randFloat) * 600.0f;
		FVector playerPos = GetOwner()->GetActorLocation();
		playerPos.Z = 0.0f;
		FVector DecalPos = playerPos + FVector(X, Y, 0.0f);

		


		AMagicDecal* decal = GetWorld()->SpawnActor<AMagicDecal>(_tedecal, fireLocation, FRotator::ZeroRotator);
		
		if (decal)
		{
			SoundManager->PlaySound(*GetEpicAttackMagicDotSound(), this->GetActorLocation());
			UE_LOG(LogTemp, Error, TEXT("Test Decal"));
			
			_monster_Epic_AnimInstance->PlayAttackDotrMontage();
			_curAttackIndex = 0;

			decal->Active(DecalPos);  
			decal->SetLifeSpan(10.0f);
		}
	}
}
