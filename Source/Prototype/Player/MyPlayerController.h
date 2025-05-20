// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MeteorDecalPool.h"
#include "MyPlayerController.generated.h"

/**
 *
 */
UCLASS()
class PROTOTYPE_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	AMyPlayerController();


	UPROPERTY()
    class USkillWidget_test* SkillWidgetInstance;

protected:
	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = Input)
	class UInputMappingContext *_inputMappingContext;

	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AMeteorDecal> MeteorDecalClass;

public:
 	UPROPERTY(EditAnywhere, Category = "Decal")
	AMeteorDecalPool* MeteorDecalPool;

    UPROPERTY(EditAnywhere, Category = "UI")
    TSubclassOf<class USkillWidget_test> SkillWidgetClass;





};
