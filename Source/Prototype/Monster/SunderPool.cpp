// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/SunderPool.h"
#include "Engine/World.h"
#include "BossSunder.h"

void USunderPool::InitializePool(UWorld* World, TSubclassOf<class ABossSunder> SunderClass, int32 InitialSize)
{
   if (!World || !SunderClass)
    {
        UE_LOG(LogTemp, Error, TEXT("Invalid parameters for InitializePool"));
        return;
    }

    PoolWorld = World;
    SunderBlueprintClass = SunderClass;

    for (int32 i = 0; i < InitialSize; ++i)
    {
        ABossSunder* NewSunder = World->SpawnActor<ABossSunder>(SunderClass);
        if (NewSunder)
        {
            NewSunder->SetActorEnableCollision(false);
            NewSunder->SetActorHiddenInGame(true);
            SunderPool.Add(NewSunder);
        }
        else
        {
            UE_LOG(LogTemp, Error, TEXT("Failed to spawn Sunder at index %d"), i);
        }
    }

    UE_LOG(LogTemp, Log, TEXT("SunderPool initialized with %d instances"), SunderPool.Num());
}

ABossSunder* USunderPool::GetPooledSunder()
{
 for (ABossSunder* Sunder : SunderPool)
    {
        if (Sunder && !Sunder->IsActive())
        {
            Sunder->SetActorEnableCollision(true);
            Sunder->SetActorHiddenInGame(false);
            return Sunder;
        }
    }

    if (PoolWorld && SunderBlueprintClass)
    {
        ABossSunder* NewSunder = PoolWorld->SpawnActor<ABossSunder>(SunderBlueprintClass);
        if (NewSunder)
        {
            SunderPool.Add(NewSunder);
            return NewSunder;
        }
    }

    UE_LOG(LogTemp, Warning, TEXT("Failed to retrieve a pooled Sunder"));
    return nullptr;
}

void USunderPool::ReturnSunderToPool(ABossSunder* Sunder)
{
     if (Sunder)
    {
        Sunder->SetActorEnableCollision(false);
        Sunder->SetActorHiddenInGame(true);
        Sunder->Deactivate();
    }
}
