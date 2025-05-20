// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/EpicProjectile.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Engine/DamageEvents.h"

#include "Player/MyPlayer.h"

#include "Monster/EpicMonster_witch.h"

// Sets default values
AEpicProjectile::AEpicProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	_EpicMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> te(
		TEXT("/Script/Engine.SkeletalMesh'/Game/SKnight_modular/Skeleton_Knight_07/mesh/weapon/SK_Arrow.SK_Arrow'"));
	if (te.Succeeded())
	{
		_EpicMesh->SetSkeletalMesh(te.Object);
	}
		
	FRotator MeshRotation = FRotator(-90.f, -90.f, 0.f);
	_EpicMesh->SetRelativeRotation(MeshRotation);

	_collider = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	_collider->InitCapsuleSize(70.f, 20.f);


	FRotator CapsuleRotation = FRotator(0.f, 0.f, 90.f);
	_collider->SetRelativeRotation(CapsuleRotation);


	_movementCom = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMove"));

	RootComponent = _EpicMesh;

	_collider->SetupAttachment(_EpicMesh);
}

// Called when the game starts or when spawned
void AEpicProjectile::BeginPlay()
{
	Super::BeginPlay();
	
	Init();

	GetWorldTimerManager().SetTimer(_timerHandle, this, &AEpicProjectile::Disable, 1.5f, false);


}

// Called every frame
void AEpicProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEpicProjectile::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	_collider->OnComponentBeginOverlap.AddDynamic(this, &AEpicProjectile::OnMyCharacterOverlap);

}

void AEpicProjectile::FireInDirection(const FVector& ShootDirection)
{
	if (_movementCom)
	{
		_movementCom->Velocity = ShootDirection * _movementCom->InitialSpeed;

	}
}

void AEpicProjectile::OnMyCharacterOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromWeep, const FHitResult& SweepResult)
{
	auto PlayerCh = Cast<AMyPlayer>(OtherActor);

	_damage = 70;

	if (PlayerCh)
	{
		FDamageEvent DamageEvent;
		AController* EventInstigator = GetInstigatorController();

		if (_Witch != nullptr)
		{
			AActor* DamageCauser = Cast<AActor>(_Witch);

			PlayerCh->TakeDamage(_damage, DamageEvent, EventInstigator, DamageCauser);

			FVector hitPos = OtherActor->GetActorLocation();

			FVector direction = _Witch->GetActorForwardVector();
			FRotator hitRotation = direction.Rotation();




		}
		Disable();
	}


	//auto player = Cast<AMyPlayer>(OtherActor);
	//Disable();
	
}

void AEpicProjectile::Init()
{
	SetActorHiddenInGame(false);
	SetActorEnableCollision(true);
}

void AEpicProjectile::Disable()
{
	SetActorHiddenInGame(true);
	SetActorEnableCollision(false);
	GetWorldTimerManager().ClearTimer(_timerHandle);
}

