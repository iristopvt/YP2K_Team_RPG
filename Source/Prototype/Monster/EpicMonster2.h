// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Monster/Monster.h"
#include "EpicMonster2.generated.h"

/**
 * 
 */
UCLASS()
class PROTOTYPE_API AEpicMonster2 : public AMonster
{
	GENERATED_BODY()

public:
	AEpicMonster2();

	

protected:
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;
};
