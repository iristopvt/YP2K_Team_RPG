// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MyGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class PROTOTYPE_API AMyGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	AMyGameModeBase();

	virtual void BeginPlay() override;

	virtual void PostInitializeComponents() override;

	void LockSkill();

	void SpawnMonster(FVector BaseLocation, FVector AddLocation);

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class APortal_Stage2_Normal> _portal2;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class ANormalMonster> _monster;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class ABossObstacle> _obstacle;
	
};
