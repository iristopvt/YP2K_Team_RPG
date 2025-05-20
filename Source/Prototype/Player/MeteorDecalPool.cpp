// Fill out your copyright notice in the Description page of Project Settings.

#include "Player/MeteorDecalPool.h"
#include "MeteorDecal.h"

// Sets default values
AMeteorDecalPool::AMeteorDecalPool()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	static ConstructorHelpers::FClassFinder<AMeteorDecal> MD(TEXT("Blueprint'/Game/Blueprint/VFX/MeteorDecal_Test_BP.MeteorDecal_Test_BP_C'"));
	if (MD.Succeeded())
	{
		MeteorClass = MD.Class;
	}
}

// Called when the game starts or when spawned
void AMeteorDecalPool::BeginPlay()
{
	Super::BeginPlay();
}

void AMeteorDecalPool::InitializePool(int32 InitialSize)
{
	for (int i = 0; i < InitialSize; i++)
	{
		if (MeteorClass)
		{
			AMeteorDecal *NewDecal = GetWorld()->SpawnActor<AMeteorDecal>(MeteorClass, FVector::ZeroVector, FRotator::ZeroRotator);
			if (NewDecal)
			{
				NewDecal->SetActorHiddenInGame(true);
				MeteorDecalPool.Add(NewDecal);
			}
		}
	}
}

class AMeteorDecal *AMeteorDecalPool::GetPoolMeteorDecal()
{
	for (AMeteorDecal *Decal : MeteorDecalPool)
	{
		if (Decal && Decal->IsHidden())
		{
			UE_LOG(LogTemp, Warning, TEXT("Returned Meteor Decal: %s"), *Decal->GetName());
			Decal->SetActorHiddenInGame(false);
			return Decal;
		}
	}
	return nullptr;
}

void AMeteorDecalPool::ReturnMeteorDecal(AMeteorDecal *MeteorDecal)
{
	if (MeteorDecal)
	{
		MeteorDecal->SetActorHiddenInGame(true);
	}
}
