// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item/Consumes/ConsumeItem.h"
#include "Gold.generated.h"

/**
 * 
 */
UCLASS()
class PROTOTYPE_API AGold : public AConsumeItem
{
	GENERATED_BODY()
	
	virtual void BeginPlay() override;

	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

	virtual void GetItem() override;
};
