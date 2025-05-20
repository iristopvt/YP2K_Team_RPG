// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Player/MyDecal.h"
#include "LandDecal.generated.h"

/**
 * 
 */
UCLASS()
class PROTOTYPE_API ALandDecal : public AMyDecal
{
	GENERATED_BODY()

public:
	virtual void DeActiveEvent(FVector location) override;	
	
};
