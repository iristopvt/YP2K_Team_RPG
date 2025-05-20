// Fill out your copyright notice in the Description page of Project Settings.


#include "VFX/ParticleEffect.h"

#include "Particles/ParticleSystemComponent.h"
#include "Particles/ParticleSystem.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"



AParticleEffect::AParticleEffect()
{

	PrimaryActorTick.bCanEverTick = false;
	//나이아가라
	_niagaraCom = CreateDefaultSubobject<UNiagaraComponent>(TEXT("NiagaraComponent"));
	RootComponent = _niagaraCom;

	// 파티클
	_particleCom = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ParticleComponent"));
	_particleCom->SetupAttachment(RootComponent);
}


void AParticleEffect::BeginPlay()
{
	Super::BeginPlay();
	// 나이아가라
	_niagaraCom->OnSystemFinished.AddDynamic(this, &AParticleEffect::End);
	End(_niagaraCom);

	// 파티클
	_particleCom->OnSystemFinished.AddDynamic(this, &AParticleEffect::EndParticle);
	EndParticle(_particleCom);
}


void AParticleEffect::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AParticleEffect::Play(FVector location, FRotator rotator)
{
	if (_niagaraCom->IsActive() || _particleCom->IsActive())
		return;

	SetActorLocationAndRotation(location, rotator);
	_niagaraCom->ActivateSystem();
	_particleCom->ActivateSystem();



}

bool AParticleEffect::IsPlaying()
{
	if (_niagaraCom->IsActive())
		return true;

	if (_particleCom->IsActive())
		return true;

	return false;

	// return _niagaraCom->IsActive();
}

void AParticleEffect::PlayOnSkeletalMesh(USkeletalMeshComponent* mesh, FName socketName)
{
	if (!_niagaraCom && !_particleCom)
		return;

	// 파티클 효과를 스켈레탈 메쉬의 소켓에 부착
	if (_niagaraCom)
	{
		_niagaraCom->AttachToComponent(mesh, FAttachmentTransformRules::SnapToTargetNotIncludingScale, socketName);
		_niagaraCom->ActivateSystem();
	}

	if (_particleCom)
	{
		_particleCom->AttachToComponent(mesh, FAttachmentTransformRules::SnapToTargetNotIncludingScale, socketName);
		_particleCom->ActivateSystem();
	}

}


void AParticleEffect::End(UNiagaraComponent* niagaraComponent)
{
	if (niagaraComponent)
		niagaraComponent->Deactivate();
}

void AParticleEffect::EndParticle(UParticleSystemComponent* particleComponent)
{
	if (particleComponent)
		particleComponent->DeactivateSystem();
}
