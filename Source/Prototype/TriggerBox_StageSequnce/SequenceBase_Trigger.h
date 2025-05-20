// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Components/WidgetComponent.h"
#include "LevelSequence.h"
#include "LevelSequencePlayer.h"
#include "LevelSequenceActor.h"
#include "MovieSceneSequencePlayer.h"
#include "Blueprint/UserWidget.h"
#include "SequenceBase_Trigger.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnMinimapVisibilityChanged);

UCLASS()
class PROTOTYPE_API ASequenceBase_Trigger : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASequenceBase_Trigger();

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnMinimapVisibilityChanged OnHideMinimap;

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnMinimapVisibilityChanged OnShowMinimap;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

protected:
	UFUNCTION()
	void PlaySequence();

	UFUNCTION()
	virtual void OnSequenceFinished();

	UFUNCTION()
	void OnTriggerEnter(UPrimitiveComponent *OverlappedComponent, AActor *OtherActor,
						UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UBoxComponent *TriggerBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sequence", meta = (AllowPrivateAccess = "true"))
	TSoftObjectPtr<ULevelSequence> LevelSequenceAsset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sequence", meta = (AllowPrivateAccess = "true"))
	ALevelSequenceActor *SequenceActor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Actor", meta = (AllowPrivateAccess = "true"))
	AActor *TriggeredActor;

	void HideSkillWidget();
	void ShowSkillWidget();
};
