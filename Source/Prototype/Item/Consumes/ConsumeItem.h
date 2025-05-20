// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item/BaseItem.h"
#include "ConsumeItem.generated.h"

UCLASS()
class PROTOTYPE_API AConsumeItem : public ABaseItem
{
	GENERATED_BODY()
	
public:
	AConsumeItem();

	virtual void UseItem() override;
};
