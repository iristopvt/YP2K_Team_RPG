// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Boss2Widget.generated.h"

/**
 * 
 */
UCLASS()
class PROTOTYPE_API UBoss2Widget : public UUserWidget
{
	GENERATED_BODY()

public:
	void UpdateBossHPBar(float Ratio);

private:
	UPROPERTY(meta = (BindWidget))
	class UProgressBar *BossHPBar;
	
};
