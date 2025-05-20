// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item/Equip/EquipItem.h"
#include "ShoulderGuard.generated.h"

/**
 * 
 */
UCLASS()
class PROTOTYPE_API AShoulderGuard : public AEquipItem
{
	GENERATED_BODY()

public:
	AShoulderGuard();
	
	virtual void BeginPlay() override;
};
