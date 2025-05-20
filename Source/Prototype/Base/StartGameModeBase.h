// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "StartGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class PROTOTYPE_API AStartGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
	AStartGameModeBase();

	virtual void BeginPlay();
	virtual void PostInitializeComponents() override;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = UI, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UUserWidget> StartLevelWidgetClass;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = UI, meta = (AllowPrivateAccess = "true"))
	class UMainStartWidget* StartLevelWidget;
};
