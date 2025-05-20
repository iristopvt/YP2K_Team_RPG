// Fill out your copyright notice in the Description page of Project Settings.

#include "Monster/Boss2Monster.h"
#include "Components/CapsuleComponent.h"
#include "TimerManager.h"
#include "AI/AIController_Boss2.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Player/MyPlayer.h"
#include "Base/MyGameInstance.h"
#include "Base/Stage2BossGameModeBase.h"
#include "Engine/DamageEvents.h"
#include "../Animation/Monster_Boss2_AnimInstance.h"
#include "BossFireball.h"
#include "SunderPool.h"
#include "BossSunder.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "Base/Managers/EffectManager.h"

ABoss2Monster::ABoss2Monster()
{
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SM(TEXT("/Script/Engine.SkeletalMesh'/Game/ParagonMinions/Characters/Minions/Prime_Helix/Meshes/Prime_Helix.Prime_Helix'"));

	if (SM.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(SM.Object);
	}

	static ConstructorHelpers::FClassFinder<ABossFireball> BF(TEXT("/Script/Engine.Blueprint'/Game/Blueprint/Monster/BossMonster/BossFireball_BP.BossFireball_BP_C'"));
	if (BF.Succeeded())
	{
		_fireball = BF.Class;
	}

	static ConstructorHelpers::FClassFinder<ABossSunder> BS(TEXT("/Script/Engine.Blueprint'/Game/Blueprint/Monster/BossMonster/BossSunder_BP.BossSunder_BP_C'"));
	if (BS.Succeeded())
	{
		_sunder = BS.Class;
	}
	
	SunderPool = NewObject<USunderPool>();

	GetCapsuleComponent()->SetCapsuleHalfHeight(310.0f);
	GetCapsuleComponent()->SetCapsuleRadius(100.0f);

	AIControllerClass = AAIController_Boss2::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

void ABoss2Monster::BeginPlay()
{
	Super::BeginPlay();

}

void ABoss2Monster::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	_bossMonster02_AnimInstance = Cast<UMonster_Boss2_AnimInstance>(GetMesh()->GetAnimInstance());
	if (_bossMonster02_AnimInstance->IsValidLowLevelFast())
	{
		_bossMonster02_AnimInstance->OnMontageEnded.AddDynamic(this, &ACreature::OnAttackEnded);
		_bossMonster02_AnimInstance->_attackDelegate.AddUObject(this, &ACreature::AttackHit);
		_bossMonster02_AnimInstance->_deathDelegate.AddUObject(this, &AMonster::Disable);
		_bossMonster02_AnimInstance->_skillDelegate.AddDynamic(this, &ABoss2Monster::FireballAttack);
	}
	 _StatCom->SetBossLevelInit(1);

}

void ABoss2Monster::FireballAttack(FVector Location)
{
	Isfire = true;
	float FireballSpacing = 200.0f;
	FVector InitialLocation = GetActorLocation() + FVector(0, 0, 300.0f);
	FRotator SpawnRotation = FRotator::ZeroRotator;

	int FireballCount = 5;
	float MiddleIndex = (FireballCount - 1) / 2.0f;

	TArray<class ABossFireball *> Fireballs;

	FVector ForwardVector = GetActorForwardVector();
	FVector RightVector = GetActorRightVector();


	for (int i = 0; i < FireballCount; i++)
	{
		FVector Offset = RightVector * (i - MiddleIndex) * FireballSpacing;
		FVector SpawnLocation = InitialLocation + Offset;

		ABossFireball *Fireball = GetWorld()->SpawnActor<ABossFireball>(_fireball, SpawnLocation, SpawnRotation);
		if (Fireball)
		{
			Fireballs.Add(Fireball);
		}
	}

	if (Fireballs.IsValidIndex(0))
	{
		Fireballs[0]->LaunchTowards(Location);
	}

	for (int i = 1; i < Fireballs.Num(); i++)
	{
		FTimerHandle TimerHandle;

		GetWorldTimerManager().SetTimer(TimerHandle, [this, Fireballs, i, Location]()
										{
            if (Fireballs.IsValidIndex(i) && Fireballs[i])
            {
                Fireballs[i]->LaunchTowards(UpdatedLocation());
            } }, i * 0.5f, false);
	}
	Isfire = false;
}

FVector ABoss2Monster::UpdatedLocation()
{
	auto AIController = Cast<AAIController_Boss2>(GetController());
	FVector LastVector;

    if (AIController && AIController->GetBlackboardComponent())
    {
        AActor* TargetActor = Cast<AActor>(AIController->GetBlackboardComponent()->GetValueAsObject("Target"));
        if (TargetActor)
        {
			LastVector = TargetActor->GetActorLocation();
            return LastVector;
        }
    }
    return LastVector;
}

float ABoss2Monster::TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	UBaseAnimInstance *AnimInstance = Cast<UBaseAnimInstance>(GetMesh()->GetAnimInstance());

	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
    if (!PlayerController) return 0.0f;

    AMyPlayer* player = Cast<AMyPlayer>(PlayerController->GetPawn());

	if (AnimInstance)
	{
		AnimInstance->PlayHitReactionMontage();
	}

	SoundManager->PlaySound(*GetGuardOff(), _hitPoint);

	_StatCom->AddCurHp(-Damage);


	if (_StatCom->IsDead())
	{
		SoundManager->PlaySound(*GetDeadSoundName(), _hitPoint);

		SetActorEnableCollision(false);
		auto controller = GetController();
		if (controller)
			GetController()->UnPossess();
		player->_StatCom->AddExp(_StatCom->GetNextExp());
		player->_inventoryComponent->GettingMoney(2000);
		GetWorld()->GetTimerManager().SetTimer(TimerHandle_Destroy, this, &ACreature::DelayedDestroy, 2.0f, false);
	}

	return 0.0f;
}



void ABoss2Monster::Attack_AI()
{
	if (_isAttacking == false && _bossMonster02_AnimInstance != nullptr)
	{
		_isAttacking = true;
		_bossMonster02_AnimInstance->PlayAttackMontage();
	}

}

void ABoss2Monster::AttackHit()
{
	TArray<FHitResult> hitResults;
	FCollisionQueryParams params(NAME_None, false, this);

	float attackRange = 1000.0f;
	float attackRadius = 200.0f;

	bool bResult = GetWorld()->SweepMultiByChannel(
		hitResults,
		GetActorLocation(),
		GetActorLocation() + GetActorForwardVector() * attackRange,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel2,
		FCollisionShape::MakeSphere(attackRadius),
		params);

	FVector vec = GetActorForwardVector() * attackRange;
	FVector center = GetActorLocation() + vec * 0.5f;

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

				EffectManager->Play(*GetBoss2AttackEffect(), _hitPoint);
				
				break;
			}
		}
	}
	else
	{
		FVector missLocation = GetActorLocation();
		SoundManager->PlaySound(*GetSwingSoundName(), missLocation);

		
	}
	//DrawDebugSphere(GetWorld(), center, attackRadius, 32, drawColor, false, 0.3f);


}

void ABoss2Monster::Skill_AI(FVector location)
{
	if (_bossMonster02_AnimInstance != nullptr)
	{
		_bossMonster02_AnimInstance->PlaySkillMontage();
		_bossMonster02_AnimInstance->SetTarget(location);
	}
}

void ABoss2Monster::Teleport(FVector location)
{
    float OriginalZ = location.Z;

    FVector TeleportLocation = location + FMath::VRand() * FMath::FRandRange(100.0f, 600.0f);
    TeleportLocation.Z = OriginalZ;


    FVector MinBounds(-1710.0f, -3790.0f, 460.0f);
    FVector MaxBounds(2190.0f, -1270.0f, 460.0f);

    TeleportLocation.X = FMath::Clamp(TeleportLocation.X, MinBounds.X, MaxBounds.X);
    TeleportLocation.Y = FMath::Clamp(TeleportLocation.Y, MinBounds.Y, MaxBounds.Y);
    TeleportLocation.Z = MinBounds.Z; 


    SetActorLocation(TeleportLocation, false, nullptr, ETeleportType::TeleportPhysics);

    FRotator CurrentRotation = GetActorRotation();
    FVector DirectionToLocation = location - TeleportLocation;
    FRotator LookAtRotation = DirectionToLocation.Rotation();
    FRotator NewRotation = FRotator(CurrentRotation.Pitch, LookAtRotation.Yaw, CurrentRotation.Roll);

    SetActorRotation(NewRotation);

	FVector EffectLocation = GetActorLocation();
	EffectLocation.Z -= 300.0f;

    EffectManager->Play(*GetBoss2TeleportEffect(), EffectLocation);
    SoundManager->PlaySound(*GetBoss2TeleportSound(), GetActorLocation());

    Attack_AI();
}

FString ABoss2Monster::GetBoss2AttackEffect() const
{
	return "NS_Mage_LIghtning_Bolt";
}

FString ABoss2Monster::GetBoss2TeleportEffect() const
{
	return "NS_Boss_02_Teleport";
}

FString ABoss2Monster::GetBoss2TeleportSound() const
{
	return "Boss_02_Teleport_Cue";
}

