// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EpicProjectile.generated.h"

UCLASS()
class PROTOTYPE_API AEpicProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEpicProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void PostInitializeComponents() override;

	void FireInDirection(const FVector& ShootDirection);

	UFUNCTION()
	void OnMyCharacterOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromWeep, const FHitResult& SweepResult);
	void WitchMa(class AEpicMonster_witch* archer) { _Witch = archer; }
	void SetDamage(int32 Amount) { _damage = Amount; }

	void Init();
	void Disable();
	


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mesh, meta = (AllowPrivateAccess = "true"))
	class USkeletalMeshComponent* _EpicMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mesh, meta = (AllowPrivateAccess = "true"))
	class UCapsuleComponent* _collider;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mesh, meta = (AllowPrivateAccess = "true"))
	class UProjectileMovementComponent* _movementCom;
	



	// witch	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Damage, meta = (AllowPrivateAccess = "true"))
	class AEpicMonster_witch* _Witch;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mesh, meta = (AllowPrivateAccess = "true"))
	int32 _damage;

	FTimerHandle _timerHandle;

};
