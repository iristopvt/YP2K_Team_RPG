// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerBox_StageSequnce/SequenceBase_Trigger.h"
#include "LevelSequence.h"
#include "LevelSequencePlayer.h"
#include "LevelSequenceActor.h"
#include "MovieSceneSequencePlayer.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "../Base/Managers/UIManager.h"

#include "UI/PlayerBarWidget.h"
#include "UI/SkillWidget_test.h"
#include "UI/MiniMapWidget.h"
#include "UI/StatWidget.h"
#include "Component/StatComponent.h"

#include "Base/Stage2BossGameModeBase.h"
#include "Base/MyGameInstance.h"
#include "Player/Creature.h"
#include "Blueprint/UserWidget.h"

#include "GameFramework/PlayerController.h"
#include "Player/MyPlayerController.h"

// Sets default values
ASequenceBase_Trigger::ASequenceBase_Trigger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
    RootComponent = TriggerBox;

    TriggerBox->SetBoxExtent(FVector(200.0f, 200.0f, 100.0f));
    TriggerBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    TriggerBox->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
    TriggerBox->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
    TriggerBox->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);

}

// Called when the game starts or when spawned
void ASequenceBase_Trigger::BeginPlay()
{
	Super::BeginPlay();

    TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &ASequenceBase_Trigger::OnTriggerEnter);

    ULevelSequence *LoadedSequence = LevelSequenceAsset.LoadSynchronous();
    if (LoadedSequence)
    {
        FMovieSceneSequencePlaybackSettings PlaybackSettings;
        PlaybackSettings.bPauseAtEnd = true;
        ALevelSequenceActor *OutActor = nullptr;
        ULevelSequencePlayer *Player = ULevelSequencePlayer::CreateLevelSequencePlayer(
            GetWorld(),
            LoadedSequence,
            PlaybackSettings,
            OutActor);

        if (Player && OutActor)
        {
            SequenceActor = OutActor;

            Player->OnFinished.AddDynamic(this,&ASequenceBase_Trigger::OnSequenceFinished);
        }
    }
	
}

// Called every frame
void ASequenceBase_Trigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASequenceBase_Trigger::OnTriggerEnter(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UIManager->CloseAll();

    ACreature *Creature = Cast<ACreature>(OtherActor);
    if (Creature)
    {
        UUserWidget *Widget = Creature->GetWidget();
        if (Widget)
        {
            Widget->SetVisibility(ESlateVisibility::Hidden);
        }

        TriggeredActor = OtherActor;

        HideSkillWidget();
        OnHideMinimap.Broadcast();

        if (OtherActor && OtherActor->IsA(ACharacter::StaticClass()))
        {
            PlaySequence();
        }
    }
}

void ASequenceBase_Trigger::PlaySequence()
{
	if (SequenceActor)
    {
        ULevelSequencePlayer *Player = SequenceActor->GetSequencePlayer();
        if (Player)
        {
            Player->Play();
        }
    }
}

void ASequenceBase_Trigger::OnSequenceFinished()
{
    if (TriggeredActor && TriggeredActor->IsA(ACreature::StaticClass()))
    {
        ACreature *Creature = Cast<ACreature>(TriggeredActor);
        if (Creature && Creature->_Widget)
        {
            Creature->_Widget->SetVisibility(ESlateVisibility::Visible);
        }
    }

    ShowSkillWidget();

    OnShowMinimap.Broadcast();

    Destroy();
}

void ASequenceBase_Trigger::HideSkillWidget()
{
	APlayerController *PlayerController = GetWorld()->GetFirstPlayerController();
    if (PlayerController)
    {
        AMyPlayerController *MyPlayerController = Cast<AMyPlayerController>(PlayerController);
        if (MyPlayerController && MyPlayerController->SkillWidgetInstance)
        {
            MyPlayerController->SkillWidgetInstance->SetVisibility(ESlateVisibility::Hidden);
        }
    }
}

void ASequenceBase_Trigger::ShowSkillWidget()
{
	APlayerController *PlayerController = GetWorld()->GetFirstPlayerController();
    if (PlayerController)
    {
        AMyPlayerController *MyPlayerController = Cast<AMyPlayerController>(PlayerController);
        if (MyPlayerController && MyPlayerController->SkillWidgetInstance)
        {
            MyPlayerController->SkillWidgetInstance->SetVisibility(ESlateVisibility::Visible);
        }
    }
}

