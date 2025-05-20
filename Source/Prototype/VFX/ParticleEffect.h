// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NiagaraComponent.h"
#include "NiagaraSystem.h"

#include "ParticleEffect.generated.h"

UCLASS()
class PROTOTYPE_API AParticleEffect : public AActor
{
	GENERATED_BODY()
	
public:	

	AParticleEffect();

protected:

	virtual void BeginPlay() override;

public:	

	virtual void Tick(float DeltaTime) override;

	void Play(FVector location, FRotator rotator);
	bool IsPlaying();

	// 스켈레톤 붙여보기 시도.
	void PlayOnSkeletalMesh(USkeletalMeshComponent* mesh, FName socketName);
	
private:
	
	UFUNCTION()
	void EndParticle(class UParticleSystemComponent* particleComponent);

	UFUNCTION()
	void End(UNiagaraComponent* niagaraComponent);

	// 나이아가라
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UNiagaraComponent* _niagaraCom;
	
	// 파티클
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UParticleSystemComponent* _particleCom;


};
