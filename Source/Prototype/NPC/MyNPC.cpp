// Fill out your copyright notice in the Description page of Project Settings.


#include "MyNPC.h"
#include "Player/MyPlayer.h"
#include "Player/MyPlayerController.h"
#include "Components/SphereComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Component/ShopComponent.h"
#include "Base/MyGameInstance.h"
#include "Base/Managers/UIManager.h"
#include "UI/ShopWidget.h"
#include "NPC_NameWidget.h"

#include "Kismet/GameplayStatics.h"

// Sets default values
AMyNPC::AMyNPC()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	_trigger = CreateDefaultSubobject<USphereComponent>(TEXT("Trigger"));
	_trigger->SetupAttachment(RootComponent);
	_trigger->SetCollisionProfileName(TEXT("NPC"));
	_trigger->SetSphereRadius(100.0f);

	_skeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
	_skeletalMesh->SetupAttachment(RootComponent);

	ConstructorHelpers::FObjectFinder<USkeletalMesh> sm(
		TEXT("/Script/Engine.SkeletalMesh'/Game/Scanned3DPeoplePack/RP_Character/rp_sophia_rigged_003_Mobile_ue4/rp_sophia_rigged_003_Mobile_ue4.rp_sophia_rigged_003_Mobile_ue4'")
	);
	if (sm.Succeeded())
	{
		_skeletalMesh->SetSkeletalMesh(sm.Object);
	}

	_shopComp = CreateDefaultSubobject<UShopComponent>(TEXT("Shop Component"));

	_nameWidget = CreateDefaultSubobject<UNPC_NameWidget>(TEXT("Name Widget"));
}

// Called when the game starts or when spawned
void AMyNPC::BeginPlay()
{
	Super::BeginPlay();
	
	_nameWidget->SetNPC_Name(_NPCName);
}

void AMyNPC::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	_trigger->OnComponentBeginOverlap.AddDynamic(this, &AMyNPC::OnOverlapBegin);
	_trigger->OnComponentEndOverlap.AddDynamic(this, &AMyNPC::OnOverlapEnd);

}

void AMyNPC::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	auto target = Cast<AMyPlayer>(OtherActor);
	if (target == nullptr)
		return;

	_target = target;
	_target->interectNPC.AddDynamic(this, &AMyNPC::Interect);

	_isOverlapped = true;
	_shopComp->SetCustomer(_target);
	//Optional : Look Player

	_nameWidget->SetVisibility(ESlateVisibility::Visible);
	_nameWidget->AddToViewport();
}

void AMyNPC::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	_target->interectNPC.RemoveDynamic(this, &AMyNPC::Interect);
	_target = nullptr;
	_isOverlapped = false;
	_shopComp->SetCustomer(_target);
	UIManager->CloseUI(UI_LIST::Shop);

	_nameWidget->SetVisibility(ESlateVisibility::Hidden);
	_nameWidget->RemoveFromParent();
}

// Called every frame
void AMyNPC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMyNPC::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AMyNPC::Interect()
{
	if (_isOverlapped == false)
		return;
	UIManager->GetShopUI()->ReflectInvenSlots(_target);
	_shopComp->OpenShop();
	UIManager->ToggleUI(UI_LIST::Shop);
}

