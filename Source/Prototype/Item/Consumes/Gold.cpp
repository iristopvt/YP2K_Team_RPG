// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/Consumes/Gold.h"
#include "Player/MyPlayer.h"
#include "Component/InventoryComponent.h"

void AGold::BeginPlay()
{
	Super::BeginPlay();

	SetItemWithCode(1);
}

void AGold::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	_player = Cast<AMyPlayer>(OtherActor);
	if (_player == nullptr)
		return;
	GetItem();
	Disable();
}

void AGold::GetItem()
{
	_player->_inventoryComponent->GettingMoney(_Value);
}
