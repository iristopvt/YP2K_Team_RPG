#include "Player/Fireball.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "MyPlayer.h"
#include "../Monster/Monster.h"
#include "Engine/DamageEvents.h"

#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "Base/MyGameInstance.h"
#include "Base/Managers/EffectManager.h"

// Sets default values
AFireball::AFireball()
{
    PrimaryActorTick.bCanEverTick = true;

    _sphereCom = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComponent"));
    _sphereCom->InitSphereRadius(15.0f);
    _sphereCom->SetCollisionProfileName(TEXT("Projectile"));
    RootComponent = _sphereCom;
       
    _niagaraCom = CreateDefaultSubobject<UNiagaraComponent>(TEXT("NS_Projectile_01"));
    _niagaraCom->SetupAttachment(RootComponent);

    _moveCom = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
    _moveCom->UpdatedComponent = _sphereCom;
    _moveCom->InitialSpeed = 0.0f;
    _moveCom->bRotationFollowsVelocity = true;
    _moveCom->ProjectileGravityScale = 0.0f;

    InitialLifeSpan = 5.0f; 
    OrbitRadius = 100.0f;  
    OrbitSpeed = 2.0f;    
    _damage = 50.f;
}

// Called when the game starts or when spawned
void AFireball::BeginPlay()
{
    Super::BeginPlay();
    _sphereCom->OnComponentBeginOverlap.AddDynamic(this, &AFireball::OnMyCharacterOverlap);

    Player = Cast<AMyPlayer>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
    StartLocation = GetActorLocation();
}

void AFireball::InitializeOrbit(float InRadius, float InAngle, int InTotalFireballCount)
{
    OrbitRadius = InRadius;
    OrbitAngle = InAngle;
    TotalFireballCount = InTotalFireballCount;
}

// Called every frame
void AFireball::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if(Player ==nullptr)
    {
        return;
    }
    OrbitAngle += OrbitSpeed * DeltaTime;
    if (OrbitAngle > 360.0f)
    {
        OrbitAngle -= 360.0f;
    }

    FVector NewLocation = GetActorLocation();
    NewLocation.X = Player->GetActorLocation().X + FMath::Cos(OrbitAngle) * OrbitRadius / 2;
    NewLocation.Y = Player->GetActorLocation().Y + FMath::Sin(OrbitAngle) * OrbitRadius / 2;
    NewLocation.Z = Player->GetActorLocation().Z;

    SetActorLocation(NewLocation);

    AMonster* NearestMonster = FindNearestMonster();
    if (NearestMonster)
    {
        Player = nullptr;
        FVector Direction = (NearestMonster->GetActorLocation() - GetActorLocation()).GetSafeNormal();

        _moveCom->Velocity = Direction * 1500.0f; 

        OrbitSpeed = 0.0f;
        OrbitRadius = 0.0f;
    }
}

AMonster* AFireball::FindNearestMonster()
{

    float SearchRadius = OrbitRadius + 150.0f;
    FVector FireballLocation = GetActorLocation();

    TArray<FHitResult> HitResults;
    FCollisionQueryParams QueryParams;
    QueryParams.AddIgnoredActor(this);

    bool bHit = GetWorld()->SweepMultiByChannel(
        HitResults,
        FireballLocation,
        FireballLocation,
        FQuat::Identity,
        ECC_GameTraceChannel2, 
        FCollisionShape::MakeSphere(SearchRadius),
        QueryParams
    );

    AMonster* NearestMonster = nullptr;
    float ShortestDistance = SearchRadius;

    if (bHit)
    {
        for (const FHitResult& Hit : HitResults)
        {
            AMonster* Monster = Cast<AMonster>(Hit.GetActor());
            if (Monster)
            {
                float Distance = FVector::Dist(FireballLocation, Monster->GetActorLocation());
                if (Distance < ShortestDistance)
                {
                    ShortestDistance = Distance;
                    NearestMonster = Monster;
                }
            }
        }
    }

    return NearestMonster;
}


void AFireball::OnMyCharacterOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    auto monster = Cast<AMonster>(OtherActor);
    if (monster)
    {
        monster->TakeDamage(_damage, FDamageEvent(), nullptr, this);
        EffectManager->Play(*GetSkill_03_HitEffect(), monster->GetActorLocation());
        SoundManager->PlaySound(*GetSkill_03_HitSound(), monster->GetActorLocation());
        Destroy();
    }
}

FString AFireball::GetSkill_03_HitEffect() const
{
    return "NS_Projectile_01_Hit";
}

FString AFireball::GetSkill_03_HitSound() const
{
    return "Skill03_Sound_Hit_Cue";
}
