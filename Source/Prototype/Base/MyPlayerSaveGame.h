// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "MyPlayerSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class PROTOTYPE_API UMyPlayerSaveGame : public USaveGame
{
	GENERATED_BODY()
public:
	UPROPERTY(VisibleAnywhere, Category="Inventory")
	TArray<FString> ItemSlotNames;

	UPROPERTY(VisibleAnywhere, Category="Inventory")
	TMap<FString, FString> EquipSlotNames;

	UPROPERTY(VisibleAnywhere, Category="Mesh")
	FString BodyMeshName;

	UPROPERTY(VisibleAnywhere, Category="Mesh")
	FString LowerBodyMeshName;

	UPROPERTY(VisibleAnywhere, Category="Mesh")
	FString ShoulderBodyMeshName;

	UPROPERTY(VisibleAnywhere, Category="Mesh")
	FString SwordBodyMeshName;

	UPROPERTY(VisibleAnywhere, Category="Mesh")
	FString ShieldBodyMeshName;
	
};
