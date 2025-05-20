// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Components/WidgetComponent.h"
#include "LevelSequence.h"
#include "LevelSequencePlayer.h"
#include "LevelSequenceActor.h"
#include "SequenceBase_Trigger.h"
#include "Blueprint/UserWidget.h"
#include "Stage02Sequence_Trigger.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnMinimap02VisibilityChanged);

class UUserWidget;
UCLASS()
class PROTOTYPE_API AStage02Sequence_Trigger : public ASequenceBase_Trigger
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AStage02Sequence_Trigger();



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

    virtual void OnSequenceFinished() override;

};
