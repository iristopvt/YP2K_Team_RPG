// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DecalActor.h"
#include "MagicDecal.generated.h"

/**
 * 
 */
UCLASS()
class PROTOTYPE_API AMagicDecal : public ADecalActor
{
	GENERATED_BODY()
	
public:
    AMagicDecal();
 
    virtual void BeginPlay() override;

    virtual void Tick(float DeltaTime) override;

    void ApplyDamageToOverlappingPlayers();

    void Active(FVector location);

    void DeActiveEvent(FVector location);


    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = DECAL, meta = (AllowPrivateAccess = "true"))
    float _damageInterval = 1.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = DECAL, meta = (AllowPrivateAccess = "true"))
    float _damageAmount = 100.0f;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = DECAL, meta = (AllowPrivateAccess = "true"))
    float _damageRadius = 300.0f;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = DECAL, meta = (AllowPrivateAccess = "true"))
    class UNiagaraComponent* _MagicDecalNiargar;
private:

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = DECAL, meta = (AllowPrivateAccess = "true"))
    float _areaRadius;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = DECAL, meta = (AllowPrivateAccess = "true"))
    float _delayTime;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = DECAL, meta = (AllowPrivateAccess = "true"))
    float _runTime;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = DECAL, meta = (AllowPrivateAccess = "true"))
    bool _bIsPlay;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = DECAL, meta = (AllowPrivateAccess = "true"))
    bool _bLoop;

 

    FTimerHandle _damageTimerHandle;


};
