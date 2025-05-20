// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/AudioComponent.h"
#include "SoundEffect.generated.h"

UCLASS()
class PROTOTYPE_API ASoundEffect : public AActor
{
	GENERATED_BODY()
	
public:	
	ASoundEffect();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	void Play(FVector location);
	bool IsPlaying() const;
	void Stop();

	float GetDuration() const;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class USoundBase* _soundCom;
	
	UPROPERTY(VisibleAnywhere)
	 UAudioComponent* _audioComponent;
};
