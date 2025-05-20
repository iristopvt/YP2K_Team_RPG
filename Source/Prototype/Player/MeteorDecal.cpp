// Fill out your copyright notice in the Description page of Project Settings.

#include "MeteorDecal.h"
#include "Components/StaticMeshComponent.h"
#include "Components/DecalComponent.h"
#include "Monster/Monster.h"
#include "MyPlayer.h"
#include "NiagaraComponent.h"
#include "Engine/DamageEvents.h"
#include "NiagaraFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"

AMeteorDecal::AMeteorDecal()
{
    PrimaryActorTick.bCanEverTick = true;
    _fallDuration = 3.0f;  // Default fall duration
    _elapsedTime = 0.0f;

    // Initialize Static Mesh for Meteor
    _niagaraCom = CreateDefaultSubobject<UNiagaraComponent>(TEXT("NiagaraComponent"));
    _niagaraCom->SetupAttachment(RootComponent);

    static ConstructorHelpers::FObjectFinder<UNiagaraSystem> NiagaraEffect(TEXT("/Script/Niagara.NiagaraSystem'/Game/RPGEffects/ParticlesNiagara/Warrior/HeavyImpact/NS_Warrior_HeavyImpact_02.NS_Warrior_HeavyImpact_02'"));
    if (NiagaraEffect.Succeeded())
    {
        _additionalEffect = NiagaraEffect.Object;
    }
}

void AMeteorDecal::BeginPlay()
{
    Super::BeginPlay();
    _elapsedTime = 0.0f;

    SetActorScale3D(FVector(1.0f, 20.0f, 20.0f));

    // Niagara 크기 설정
    if (_niagaraCom)
    {
        _niagaraCom->SetWorldScale3D(FVector(1.0f, 1.0f, 1.0f));
    }
}

void AMeteorDecal::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (_elapsedTime < _fallDuration)
    {
        _elapsedTime += DeltaTime;
        UpdateMeteorPosition(DeltaTime);

        float progress = _elapsedTime / _fallDuration;
        FVector curScale = GetActorScale();
        curScale.Y = progress * _areaRadius;
        curScale.Z = progress * _areaRadius;
        SetActorScale3D(curScale);

        if (_elapsedTime >= _fallDuration)
        {
            OnMeteorImpact();
        }
    }
}

void AMeteorDecal::StartMeteor(FVector startLocation, FVector endLocation, float fallDuration)
{
    _startLocation = startLocation;
    _endLocation = endLocation;
    _fallDuration = fallDuration;
    _elapsedTime = 0.0f;
    _niagaraCom->SetWorldLocation(startLocation);

    SetActorLocation(endLocation); 
    _bIsPlay = true;
}

void AMeteorDecal::OnMeteorImpact()
{
    _fieldAttackDelegate.Broadcast(GetActorLocation());

    _niagaraCom->SetVisibility(false);

    if (_additionalEffect)
    {
        UNiagaraFunctionLibrary::SpawnSystemAtLocation(
            GetWorld(),
            _additionalEffect,
            GetActorLocation(), 
            FRotator::ZeroRotator,
            FVector(10.0f)
        );
    }

   
    float DamageAmount = 500.0f;
    FVector DecalSize = GetDecal()->DecalSize;
    float Size = DecalSize.Y;
    float DamageRadius = _areaRadius * Size;

    TArray<AActor*> IgnoredActors;

    AMyPlayer* Player = Cast<AMyPlayer>(GetWorld()->GetFirstPlayerController()->GetPawn());
    if (Player)
    {
        IgnoredActors.Add(Player);
    }

    UGameplayStatics::ApplyRadialDamage(
        GetWorld(),
        DamageAmount,
        GetActorLocation(),
        DamageRadius,
        UDamageType::StaticClass(),
        IgnoredActors,
        this,
        GetInstigatorController(),
        true
    );

    // 데칼 폭발 처리
    DeActiveEvent(GetActorLocation());
}

void AMeteorDecal::UpdateMeteorPosition(float DeltaTime)
{
    FVector currentLocation = FMath::Lerp(_startLocation, _endLocation, _elapsedTime / _fallDuration);
    _niagaraCom->SetWorldLocation(currentLocation);
}

void AMeteorDecal::DeActiveEvent(FVector location)
{


}