// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Stage2BossGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class PROTOTYPE_API AStage2BossGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	AStage2BossGameModeBase();

	virtual void BeginPlay() override;

	virtual void PostInitializeComponents() override;

	void BossClear();

	void BossStart();

	void LockSkill();


private:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class ABoss2Monster> _boss;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class APortal_Home> _portal;

};
