// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item/Equip/EquipItem.h"
#include "LowerArmor.generated.h"

/**
 * 
 */
UCLASS()
class PROTOTYPE_API ALowerArmor : public AEquipItem
{
	GENERATED_BODY()

public:
	ALowerArmor();
	
	virtual void BeginPlay() override;
};
