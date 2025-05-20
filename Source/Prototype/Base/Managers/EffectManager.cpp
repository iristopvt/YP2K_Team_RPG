// Fill out your copyright notice in the Description page of Project Settings.


#include "Base/Managers/EffectManager.h"

#include "Components/SceneComponent.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "Particles/ParticleSystem.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "VFX/ParticleEffect.h"



AEffectManager::AEffectManager()
{
	PrimaryActorTick.bCanEverTick = false;

	_rootComponent = CreateDefaultSubobject<USceneComponent>("RootComponent");
	RootComponent = _rootComponent;

	//Player : Skill 1 Teleport Niagara
	CreateNiagaraClass(TEXT("NS_Teleport"), TEXT("/Script/Engine.Blueprint'/Game/Blueprint/VFX/Niagara/NS_Skill04_Start_BP.NS_Skill04_Start_BP_C'"));
	
	//Player : Skill 2 Meteor Niagara
	CreateNiagaraClass(TEXT("NS_Meteor"), TEXT("/Script/Engine.Blueprint'/Game/Blueprint/VFX/NS_Meteor_BP.NS_Meteor_BP_C'"));
	
	//Player : AttakHit Particle
	CreateNiagaraClass(TEXT("P_Greystone_Novaborn_Primary_Impact"), TEXT("/Script/Engine.Blueprint'/Game/Blueprint/VFX/Particle/P_PlayerAttackHit_BP.P_PlayerAttackHit_BP_C'"));

	//Plaer : Skill 3 FireBall Niagara
	CreateNiagaraClass(TEXT("NS_Projectile_01"), TEXT("/Script/Engine.Blueprint'/Game/Blueprint/VFX/Niagara/NS_FireBall_BP.NS_FireBall_BP_C'"));
	CreateNiagaraClass(TEXT("NS_Projectile_01_Hit"), TEXT("/Script/Engine.Blueprint'/Game/Blueprint/VFX/Niagara/NS_FireBallHit_BP.NS_FireBallHit_BP_C'"));

	//Player : Skill 4 
	CreateNiagaraClass(TEXT("NS_Skill04_Start"), TEXT("/Script/Engine.Blueprint'/Game/Blueprint/VFX/Niagara/NS_Skill04_Start_BP.NS_Skill04_Start_BP_C'"));
	CreateNiagaraClass(TEXT("NS_Priest_Sphere"), TEXT("/Script/Engine.Blueprint'/Game/Blueprint/VFX/Niagara/NS_Skill04_During.NS_Skill04_During_C'"));

	//Player : Level Up
	CreateNiagaraClass(TEXT("P_Status_LevelUp"), TEXT("/Script/Engine.Blueprint'/Game/Blueprint/VFX/Particle/P_LevelUp_BP.P_LevelUp_BP_C'"));

	// EpicMonster : Skeleton Spawn
	CreateNiagaraClass(TEXT("P_Morigesh_Ultimate_Reveal"), TEXT("/Script/Engine.Blueprint'/Game/Blueprint/VFX/Particle/P_Epic_Skeleton.P_Epic_Skeleton_C'"));

	// BossMonster : Obstacle Break
	CreateNiagaraClass(TEXT("NS_LightningSlash"), TEXT("/Script/Engine.Blueprint'/Game/Blueprint/VFX/Niagara/NS_Obstacle_Break_BP.NS_Obstacle_Break_BP_C'"));

	// Item
	CreateNiagaraClass(TEXT("I_ItemAura"), TEXT("/Script/Niagara.NiagaraSystem'/Game/MixedVFX/Particles/Mix/NS_Mix_03.NS_Mix_03'"));

	// Find Target
	CreateNiagaraClass(TEXT("NS_FindTarget"), TEXT("/Script/Engine.Blueprint'/Game/Blueprint/VFX/Niagara/NS_FindTarget_BP.NS_FindTarget_BP_C'"));

	// Boss02 Attack Hit Effect
	CreateNiagaraClass(TEXT("NS_Mage_LIghtning_Bolt"), TEXT("/Script/Engine.Blueprint'/Game/Blueprint/VFX/Niagara/NS_Boss02_Effeck_BP.NS_Boss02_Effeck_BP_C'"));
	// Boss02 Teleport
	CreateNiagaraClass(TEXT("NS_Boss_02_Teleport"), TEXT("/Script/Engine.Blueprint'/Game/Blueprint/VFX/Niagara/NS_Boss_02_Teleport_BP.NS_Boss_02_Teleport_BP_C'"));
}

void AEffectManager::CreateNiagaraClass(FString name, FString path)
{
	//ConstructorHelpers::FClassFinder<UNiagaraSystem> effect(*path);
	ConstructorHelpers::FClassFinder<AParticleEffect> effect(*path);
	if (effect.Succeeded())
	{
		_classTable.Add(name, effect.Class);
	}

}

void AEffectManager::CreateEffect()
{
	for (auto classPair : _classTable)
	{
		FString name = classPair.Key;
		_effectTable.Add(name);

		for (int32 i = 0; i < _poolCount; i++)
		{
			FString tempName = name + FString::FromInt(i);
			FActorSpawnParameters params;
			params.Name = FName(*tempName);
			auto effect = GetWorld()->SpawnActor<AParticleEffect>(classPair.Value, FVector::ZeroVector, FRotator::ZeroRotator, params);

			effect->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);
			_effectTable[name].Add(effect);
		}
	}
}

void AEffectManager::Play(FString name, FVector location, FRotator rotator)
{

	if (!_effectTable.Contains(name))
		return;

	auto findEffect = _effectTable[name].FindByPredicate(
		[](AParticleEffect* effect)-> bool
		{
			return !effect->IsPlaying();
		});

	if (findEffect)
		(*findEffect)->Play(location, rotator);


}

void AEffectManager::PlayOnSkeletalMesh(FString name, USkeletalMeshComponent* mesh, FName socketName)
{
	if (!_effectTable.Contains(name))
		return;

	auto findEffect = _effectTable[name].FindByPredicate(
		[](AParticleEffect* effect)-> bool
		{
			return !effect->IsPlaying();
		});

	if (findEffect)
		(*findEffect)->PlayOnSkeletalMesh(mesh, socketName);


}

void AEffectManager::PlayEffect(UParticleSystem* Particle, FVector Location)
{
	if (Particle)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), Particle, Location);
	}
}





void AEffectManager::BeginPlay()
{
	Super::BeginPlay();
	
	CreateEffect();


}


void AEffectManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

