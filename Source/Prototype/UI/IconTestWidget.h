// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "IconTestWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROTOTYPE_API UIconTestWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	void UpdateLocation( FVector2D& InPosition);

	UPROPERTY(meta = (BindWidget))
	class UImage* conImage;


	
};
