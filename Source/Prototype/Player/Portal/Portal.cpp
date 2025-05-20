// Fill out your copyright notice in the Description page of Project Settings.


#include "Portal.h"
#include "Components/BoxComponent.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "../../Component/InventoryComponent.h"
#include "../../Base/MyGameInstance.h"
#include "../../Base/Managers/UIManager.h"
#include "../MyPlayer.h"

// Sets default values
APortal::APortal()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	_triggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	_niagaraCom = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Niagara"));
	RootComponent = _triggerBox;

    _niagaraCom->SetupAttachment(RootComponent);

	_triggerBox->OnComponentBeginOverlap.AddDynamic(this,&APortal::OnOverlapBegin);

}

// Called when the game starts or when spawned
void APortal::BeginPlay()
{
	Super::BeginPlay();
	
}

void APortal::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
	AMyPlayer* player = Cast<AMyPlayer>(OtherActor);
    if (player)
    {
        player->ClearSkillTimer();
        UMyGameInstance* GameInstance = Cast<UMyGameInstance>(GetGameInstance());
        if (GameInstance)
        {
            UIManager->CloseAll();
            UIManager->OpenUI(UI_LIST::Load);
            GameInstance->SavePlayerStats(player->_StatCom);
            GameInstance->SaveInventory(player->_inventoryComponent);
            GameInstance->SavePlayerSkeletal(player);
            UGameplayStatics::OpenLevel(this,_mapName);
        }
    }
}


