// Fill out your copyright notice in the Description page of Project Settings.


#include "VFX/SoundEffect.h"
#include "Components/AudioComponent.h"
#include "Sound/SoundBase.h"

// Sets default values
ASoundEffect::ASoundEffect()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	_audioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComponent"));
	RootComponent = _audioComponent;
	_audioComponent->bAutoActivate = false;


}

// Called when the game starts or when spawned
void ASoundEffect::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASoundEffect::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASoundEffect::Play(FVector location)
{

	if (_audioComponent && _soundCom)
	{
		SetActorLocation(location);
		_audioComponent->SetSound(_soundCom);
		_audioComponent->Play();
	}
}

bool ASoundEffect::IsPlaying() const
{
	return _audioComponent->IsPlaying();
}

void ASoundEffect::Stop()
{
	if (IsPlaying())
	{
		_audioComponent->Stop();
	}
}

float ASoundEffect::GetDuration() const
{
	float Duration = _soundCom ? _soundCom->GetDuration() : 0.1f;
	UE_LOG(LogTemp, Warning, TEXT("Sound Duration: %f"), Duration);
	return Duration;
}




