// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/ShopComponent.h"
#include "Base/MyGameInstance.h"
#include "Base/Managers/UIManager.h"
#include "NPC/MyNPC.h"
#include "UI/ShopWidget.h"
#include "Player/MyPlayer.h"

// Sets default values for this component's properties
UShopComponent::UShopComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UShopComponent::BeginPlay()
{
	Super::BeginPlay();

	Init();
}

void UShopComponent::SetCustomer(AMyPlayer* target)
{
	_customer = target;
}

void UShopComponent::Init()
{
	int32 shopCode = Cast<AMyNPC>(GetOwner())->GetShopCode();

	SetSales(shopCode);
	UIManager->GetShopUI()->BuySucceed.AddUObject(this, &UShopComponent::Sale);
	UIManager->GetShopUI()->SaleItem.AddUObject(this, &UShopComponent::SalePlayerItem);
}

void UShopComponent::SetSales(int32 code)
{
	auto data = GAMEINSTANCE->GetSellingData(code);
	ABaseItem* item;
	for (auto it : data)
	{
		if (it == nullptr)
			continue;
		item = GAMEINSTANCE->SellDataToItemData(it);
		_sallings.Add(item);
	}
}

void UShopComponent::OpenShop()
{
	UIManager->GetShopUI()->UpdateShopList(_sallings);
}

void UShopComponent::Sale(int32 index)
{
	if (_customer == nullptr)
		return;
	
	auto p_inventory = _customer->_inventoryComponent;

	ABaseItem* merch = nullptr;
	if (_sallings[index]->GetType() == ItemType::Consume)
	{
		merch = GetWorld()->SpawnActor<ABaseItem>(ABaseItem::StaticClass(), FVector::ZeroVector, FRotator::ZeroRotator);
		merch->SetItemWithCode(_sallings[index]->GetCode());
	}
	else if (_sallings[index]->GetType() == ItemType::Equipment)
	{
		AEquipItem* EquipItem = GetWorld()->SpawnActor<AEquipItem>(AEquipItem::StaticClass(), FVector::ZeroVector, FRotator::ZeroRotator);
		EquipItem->SetItemWithCode(_sallings[index]->GetCode());
		EquipItem->SetEquipType(_sallings[index]->GetEquip());
		merch = EquipItem;
	}
	merch->SetPlayer();

	p_inventory->GettingMoney(-merch->GetPrice());
	p_inventory->AddItem(0, merch);
	UIManager->GetShopUI()->ReflectInvenSlots(_customer);
}

void UShopComponent::SalePlayerItem(int32 index, int32 amount)
{
	if (_customer == nullptr)
		return;

	auto p_inventory = _customer->_inventoryComponent;

	p_inventory->DeleteItem(index);
	p_inventory->GettingMoney(amount);
	UIManager->GetShopUI()->ReflectInvenSlots(_customer);
}

