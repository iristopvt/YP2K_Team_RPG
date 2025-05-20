// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Fireball.generated.h"

UCLASS()
class PROTOTYPE_API AFireball : public AActor
{
    GENERATED_BODY()

public:    
    // Sets default values for this actor's properties
    AFireball();

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

public:    
    // Called every frame
    virtual void Tick(float DeltaTime) override;

    void InitializeOrbit(float InRadius, float InAngle, int InTotalFireballCount);

    // Overlap event function
    UFUNCTION()
    void OnMyCharacterOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

    virtual FString GetSkill_03_HitEffect() const;
    virtual FString GetSkill_03_HitSound() const;

private:
    UPROPERTY(VisibleAnywhere, Category = "Components")
    class USphereComponent* _sphereCom;

   
    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
    class UNiagaraComponent* _niagaraCom;


    UPROPERTY(VisibleAnywhere, Category = "Movement")
    class UProjectileMovementComponent* _moveCom;

    class AMyPlayer* Player;

    FVector StartLocation;
    float OrbitRadius;
    float OrbitAngle;
    float OrbitSpeed;
    int TotalFireballCount;

    float _damage;

    class AMonster* FindNearestMonster();
};
