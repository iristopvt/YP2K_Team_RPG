// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Portal.generated.h"

UCLASS()
class PROTOTYPE_API APortal : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APortal();
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

    UPROPERTY(VisibleAnywhere, Category = "Components")
    class UBoxComponent* _triggerBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = "true"))
    class UNiagaraComponent* _niagaraCom;

	UPROPERTY(VisibleAnywhere, Category = "Portal")
    FName _mapName;

    UFUNCTION()
    void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);

};
