// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MiniMapWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROTOTYPE_API UMiniMapWidget : public UUserWidget
{
	GENERATED_BODY()
public:

	//UPROPERTY(meta = (BindWidget))
	//class UImage* MiniMapImage;
	UPROPERTY(meta = (BindWidget))
	class UImage* MapImage;
protected:
	virtual void NativeConstruct() override;
};
