// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item/Equip/EquipItem.h"
#include "UpperArmor.generated.h"

/**
 * 
 */
UCLASS()
class PROTOTYPE_API AUpperArmor : public AEquipItem
{
	GENERATED_BODY()
	
public:
	AUpperArmor();
	
	virtual void BeginPlay() override;
};
