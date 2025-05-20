// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Stage2NormalGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class PROTOTYPE_API AStage2NormalGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	AStage2NormalGameModeBase();

	virtual void BeginPlay() override;

	virtual void PostInitializeComponents() override;

	
};
