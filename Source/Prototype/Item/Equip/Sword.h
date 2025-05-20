// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item/Equip/EquipItem.h"
#include "Sword.generated.h"

/**
 * 
 */
UCLASS()
class PROTOTYPE_API ASword : public AEquipItem
{
	GENERATED_BODY()

public:
	ASword();
	
	virtual void BeginPlay()override;
};
