// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Boss1Widget.generated.h"

/**
 *
 */
UCLASS()
class PROTOTYPE_API UBoss1Widget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;
	
	void UpdateBossHPBar(float Ratio);

	void UpdateHPBarColor(int32 DestroyCount);

	void UpdateObstacleIcons(int32 DestroyCount);


private:
	UPROPERTY(meta = (BindWidget))
	class UProgressBar *BossHPBar;

	UPROPERTY(meta = (BindWidget))
	class UHorizontalBox *ObstacleIconBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Boss UI", meta = (AllowPrivateAccess = "true"))
	TArray<class UImage *> ObstacleIcons;

	class UImage *ObstacleIcon1;
	class UImage *ObstacleIcon2;
	class UImage *ObstacleIcon3;
	class UImage *ObstacleIcon4;



};
