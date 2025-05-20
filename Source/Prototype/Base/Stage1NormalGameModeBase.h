// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Stage1NormalGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class PROTOTYPE_API AStage1NormalGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	AStage1NormalGameModeBase();

	virtual void BeginPlay() override;

	virtual void PostInitializeComponents() override;

};
