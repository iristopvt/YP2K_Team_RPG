// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BossObstacle.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDestroyedDelegate);

UCLASS()
class PROTOTYPE_API ABossObstacle : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABossObstacle();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnDestroyedDelegate OnDestroyedEvent;

	UFUNCTION()
    void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

	virtual FString GetObstacleBreakEffect() const;
	virtual FString GetObstacleBreakSound() const;
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Collision", meta = (AllowPrivateAccess = "true"))
    class UBoxComponent* CollisionBox;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Mesh", meta = (AllowPrivateAccess = "true"))
    class UStaticMeshComponent* ObstacleMesh;


	// UPROPERTY()
	// class AEffectManager* EffectManager;

	
};
