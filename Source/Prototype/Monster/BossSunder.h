// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BossSunder.generated.h"

UCLASS()
class PROTOTYPE_API ABossSunder : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABossSunder();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Activate();
    void Deactivate();

    bool IsActive() const;

private:
    UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Effects",meta = (AllowPrivateAccess = "true"))
    class UNiagaraComponent* LightningEffect;

     UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Effects",meta = (AllowPrivateAccess = "true"))
    class UBoxComponent* CollisionBox;

	bool bIsActive = false;

};
