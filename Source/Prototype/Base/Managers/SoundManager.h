// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Sound/SoundCue.h"
#include "SoundManager.generated.h"

class ASoundEffect;

UCLASS()
class PROTOTYPE_API ASoundManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASoundManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void Destroy();
	void CreateSound(FString name, FString path);				// Sound종류

public:	
	virtual void Tick(float DeltaTime) override;
	void PlaySound(FString name, FVector location);
	void PlaySoundWithDuration(FString name, FVector location, float duration);
	void PlaySoundOnce(FString name, FVector location);
	void HandleAudioFinished(UAudioComponent* AudioComponent);

private:
	FTimerHandle SoundDurationTimerHandle;


	UPROPERTY()
	USceneComponent* _rootComponent;
	int32 _poolCount = 5;

	UPROPERTY()
	TMap<FString, TSubclassOf<ASoundEffect>> _soundTable;
	
	TMap<FString, TArray<ASoundEffect*>> _soundEffectTable;

	void CreateSoundEffect();

	FTimerHandle SoundEffectTimerHandle;

	TMap<FString, ASoundEffect*> ActiveSounds;

};
