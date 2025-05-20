// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/World.h"
#include "SunderPool.generated.h"

/**
 * 
 */
UCLASS()
class PROTOTYPE_API USunderPool : public UObject
{
	GENERATED_BODY()

public:
    void InitializePool(UWorld* World, TSubclassOf<class ABossSunder> SunderClass, int32 InitialSize);

    ABossSunder* GetPooledSunder();
    void ReturnSunderToPool(ABossSunder* Sunder);

private:
    UPROPERTY()
    TArray<class ABossSunder*> SunderPool;

    UPROPERTY()
    UWorld* PoolWorld = nullptr;

    TSubclassOf<class ABossSunder> SunderBlueprintClass = nullptr;
	
};
