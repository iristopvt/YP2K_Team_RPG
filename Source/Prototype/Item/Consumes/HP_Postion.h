// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item/Consumes/ConsumeItem.h"
#include "HP_Postion.generated.h"

/**
 * 
 */
UCLASS()
class PROTOTYPE_API AHP_Postion : public AConsumeItem
{
	GENERATED_BODY()
public:
	AHP_Postion();

	virtual void BeginPlay() override;

};
