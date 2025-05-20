// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DecalActor.h"
#include "MyDecal.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FieldAttack, FVector);

/**
 *
 */
UCLASS()
class PROTOTYPE_API AMyDecal : public ADecalActor
{
	GENERATED_BODY()

public:
	AMyDecal();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	void Active(FVector location);
	virtual void DeActiveEvent(FVector location);

	void SetLoop(bool loop) { _bLoop = loop; }
	void SetTime (float time) {_delayTime = time;}

	FieldAttack _fieldAttackDelegate;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = DECAL, meta = (AllowPrivateAccess = "true"))
	float _areaRadius;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = DECAL, meta = (AllowPrivateAccess = "true"))
	float _delayTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = DECAL, meta = (AllowPrivateAccess = "true"))
	float _runTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = DECAL, meta = (AllowPrivateAccess = "true"))
	bool _bIsPlay = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = DECAL, meta = (AllowPrivateAccess = "true"))
	bool _bLoop = false;
};
