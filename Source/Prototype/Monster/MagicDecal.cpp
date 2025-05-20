// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/MagicDecal.h"
#include "Engine/DecalActor.h"

#include "Components/DecalComponent.h"
#include "Engine/DamageEvents.h"
#include "Kismet/GameplayStatics.h"
#include "Player/MyPlayer.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"

AMagicDecal::AMagicDecal()
{
	PrimaryActorTick.bCanEverTick = true;
    _damageInterval = 1.0f;
    _damageAmount = 100.0f;
    _MagicDecalNiargar = CreateDefaultSubobject<UNiagaraComponent>(TEXT("MagicNiagaraComponent"));

}

void AMagicDecal::BeginPlay()
{
    Super::BeginPlay();

    _runTime = 0.0f;
    _bIsPlay = true;
  

    GetWorldTimerManager().SetTimer(_damageTimerHandle, this, &AMagicDecal::ApplyDamageToOverlappingPlayers, _damageInterval, true);

}

void AMagicDecal::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

}

void AMagicDecal::ApplyDamageToOverlappingPlayers()
{

    TArray<AActor*> OverlappingActors;
    FVector DecalLocation = GetActorLocation();

    UGameplayStatics::GetAllActorsOfClass(GetWorld(), AMyPlayer::StaticClass(), OverlappingActors);

    for (AActor* Actor : OverlappingActors)
    {
        FVector ActorLocation = Actor->GetActorLocation();
        float DistanceToDecal = FVector::Dist(DecalLocation, ActorLocation);

        if (DistanceToDecal <= _damageRadius)
        {
            AMyPlayer* Player = Cast<AMyPlayer>(Actor);
            if (Player)
            {
                FDamageEvent DamageEvent;
                Player->TakeDamage(_damageAmount, DamageEvent, nullptr, this);
            }
        }
    }
}

void AMagicDecal::Active(FVector location)
{
    _bIsPlay = true;
    SetActorLocation(location);
    _MagicDecalNiargar->SetWorldLocation(location);
}

void AMagicDecal::DeActiveEvent(FVector location)
{
    GetWorldTimerManager().ClearTimer(_damageTimerHandle);

}
