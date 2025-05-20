// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item/Equip/EquipItem.h"
#include "Helmet.generated.h"

/**
 * 
 */
UCLASS()
class PROTOTYPE_API AHelmet : public AEquipItem
{
	GENERATED_BODY()

public:
	AHelmet();
	
	virtual void BeginPlay() override;

};
