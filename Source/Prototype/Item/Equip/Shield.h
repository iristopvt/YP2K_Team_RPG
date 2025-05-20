// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item/Equip/EquipItem.h"
#include "Shield.generated.h"

/**
 * 
 */
UCLASS()
class PROTOTYPE_API AShield : public AEquipItem
{
	GENERATED_BODY()

public:
	AShield();
	
	virtual void BeginPlay() override;
};
