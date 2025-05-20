// Fill out your copyright notice in the Description page of Project Settings.

#include "Component/InventoryComponent.h"
#include "Kismet/GameplayStatics.h"

#include "Base/MyGameInstance.h"
#include "Base/Managers/UIManager.h"
#include "UI/InventoryWidget.h"

#include "Item/BaseItem.h"
#include "Item/Consumes/ConsumeItem.h"
#include "Item/Equip/EquipItem.h"
#include "Item/Equip/Helmet.h"
#include "Item/Equip/UpperArmor.h"
#include "Item/Equip/ShoulderGuard.h"
#include "Item/Equip/LowerArmor.h"
#include "Item/Equip/Sword.h"
#include "Item/Equip/Shield.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();
	if (UIManager && UIManager->GetInventoryUI())
	{
		UIManager->GetInventoryUI()->ItemDrop.AddUObject(this, &UInventoryComponent::ExcuteItem);
		UIManager->GetInventoryUI()->ItemEquip.AddUObject(this, &UInventoryComponent::EquipItem);
		UIManager->GetInventoryUI()->EquipDrop.AddUObject(this, &UInventoryComponent::ExcuteEquip);
		UIManager->GetInventoryUI()->EquipStrip.AddUObject(this, &UInventoryComponent::StripEquip);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("UIManager or Inventory UI is null in UInventoryComponent::BeginPlay"));
	}

	// InitSlot();

	UpdateUI();
}

void UInventoryComponent::InitSlot()
{
	_ItemSlots.Init(nullptr, _itemSlotMax);

	_EquipSlots.Add(TEXT("Helmet"));
	_EquipSlots.Add(TEXT("UpperArmor"));
	_EquipSlots.Add(TEXT("ShoulderArmor"));
	_EquipSlots.Add(TEXT("LowerArmor"));
	_EquipSlots.Add(TEXT("Sword"));
	_EquipSlots.Add(TEXT("Shield"));
}
// Called every frame
void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UInventoryComponent::SlotFullCheck()
{
	for (int i = 0; i < _itemSlotMax; i++)
	{
		if (_ItemSlots[i] == nullptr)
		{
			_isSlotFull = false;
			return;
		}
	}
	_isSlotFull = true;
}

void UInventoryComponent::AddItem(int32 slot, ABaseItem *item)
{
	if (item == nullptr)
		return;
	if (slot >= _itemSlotMax)
		return;
	if (_isSlotFull)
		return;
	// Fill into EmptySlot First
	if (!_EmptySlots.IsEmpty())
	{
		// TODO : Filling Already filled slot
		int32 emptyslot;
		_EmptySlots.HeapPop(emptyslot, true);
		if (_ItemSlots[emptyslot] == nullptr)
		{
			SlotFullCheck();
			_ItemSlots[emptyslot] = item;
			UIupdate_Add(emptyslot, item);
			return;
		}
	}
	// Fill into Selected Slot
	if (_ItemSlots[slot] == nullptr)
	{
		_ItemSlots[slot] = item;
		UIupdate_Add(slot, item);
		SlotFullCheck();
	}
	// if Already filled, fill into next slot
	else
	{
		for (int i = slot; i < _itemSlotMax; i++)
		{
			if (_ItemSlots[i] != nullptr)
				continue;
			_ItemSlots[i] = item;
			UIupdate_Add(i, item);
			SlotFullCheck();
			return;
		}
		return;
	}
}

void UInventoryComponent::InitializeComponent()
{
	Super::InitializeComponent();
	UIManager->GetInventoryUI()->ItemDrop.AddUObject(this, &UInventoryComponent::ExcuteItem);
}

void UInventoryComponent::ExcuteItem(int32 slot, bool isDrop)
{
	if (_ItemSlots[slot] == nullptr)
		return;
	if (slot >= _itemSlotMax)
		return;

	FVector playerPlos = GetOwner()->GetActorLocation();

	float randFloat = FMath::FRandRange(0, PI * 2.0f);

	float X = cosf(randFloat) * 300.0f;
	float Y = sinf(randFloat) * 300.0f;
	FVector itemPos = playerPlos + FVector(X, Y, 0.0f);
	itemPos.Z = 50.0f;

	UIupdate_Pop(slot);

	if (isDrop)
		_ItemSlots[slot]->DropItem(itemPos);
	else
	{
		_ItemSlots[slot]->UseItem();

	}


	_ItemSlots[slot] = nullptr;
	_EmptySlots.Add(slot);
}

void UInventoryComponent::DeleteItem(int32 slot)
{
	if (_ItemSlots[slot] == nullptr)
		return;
	if (slot >= _itemSlotMax)
		return;

	_ItemSlots[slot] = nullptr;
	_EmptySlots.Add(slot);

	UIupdate_Pop(slot);
}

void UInventoryComponent::ExcuteEquip(FString part)
{
	if (_EquipSlots[part] == nullptr)
		return;

	FVector playerPlos = GetOwner()->GetActorLocation();

	float randFloat = FMath::FRandRange(0, PI * 2.0f);

	float X = cosf(randFloat) * 300.0f;
	float Y = sinf(randFloat) * 300.0f;
	FVector itemPos = playerPlos + FVector(X, Y, 0.0f);
	itemPos.Z = 50.0f;

	_EquipSlots[part]->DropItem(itemPos);
	_EquipSlots[part] = nullptr;

	UIupdate_Pop(part);
}

void UInventoryComponent::EquipItem(int32 slot)
{
	// TODO : Switch-case with EquipType Enum later
	auto equipment = Cast<AEquipItem>(_ItemSlots[slot]);
	if (equipment == nullptr)
		return;

	switch (equipment->GetEquipType())
	{
	case EItemType::Helmet:
		TryEquip(TEXT("Helmet"), slot);
		break;
	case EItemType::UpperArmor:
		TryEquip(TEXT("UpperArmor"), slot);
		break;
	case EItemType::LowerArmor:
		TryEquip(TEXT("LowerArmor"), slot);
		break;
	case EItemType::ShoulderArmor:
		TryEquip(TEXT("ShoulderArmor"), slot);
		break;
	case EItemType::Sword:
		TryEquip(TEXT("Sword"), slot);
		break;
	case EItemType::Shield:
		TryEquip(TEXT("Shield"), slot);
		break;
	default:
		break;
	}
}

void UInventoryComponent::TryEquip(FString part, int32 slot)
{
	// if there is already filled, exchange each.
	auto equipment = Cast<AEquipItem>(_ItemSlots[slot]);
	if (equipment == nullptr)
		return;

	if (_EquipSlots[part] != nullptr)
	{
		_EquipSlots[part]->UnEquip();
		_ItemSlots[slot] = _EquipSlots[part];
	}
	else
		_ItemSlots[slot] = nullptr;

	_EquipSlots[part] = equipment;
	_EquipSlots[part]->UseItem();

	UIupdate_Add(slot, _ItemSlots[slot]);
	UIupdate_equip(part, equipment);
}

void UInventoryComponent::StripEquip(FString part)
{
	if (_EquipSlots[part] == nullptr)
		return;

	AEquipItem* equipment = _EquipSlots[part];

	if (_isSlotFull)
	{
		ExcuteEquip(part);
	}
	else
	{
		_EquipSlots[part]->UnEquip();
		UIupdate_Pop(part);
		AddItemToSlot(equipment);
	}
	_EquipSlots[part] = nullptr;
}

void UInventoryComponent::UIupdate_Add(int32 slot, ABaseItem *item)
{
	UIManager->GetInventoryUI()->UpdateItemSlot(slot, item);
}

void UInventoryComponent::UIupdate_Pop(int32 slot)
{
	UIManager->GetInventoryUI()->UpdateItemSlot(slot, nullptr);
}

void UInventoryComponent::UIupdate_Pop(FString part)
{
	UIManager->GetInventoryUI()->UpdateEquipSlot(part, nullptr);
}

void UInventoryComponent::UIupdate_equip(FString slot, ABaseItem *item)
{
	if (UIManager && UIManager->GetInventoryUI())
    {
        UIManager->GetInventoryUI()->UpdateEquipSlot(slot,item);
    }
}


void UInventoryComponent::AddItemToSlot(ABaseItem *Item)
{
	if (Item == nullptr)
		return;
	if (_isSlotFull)
		return;

	for (int i = 0; i < _itemSlotMax; i++)
	{
		if (_ItemSlots[i] == nullptr)
		{
			_ItemSlots[i] = Item;
			UIupdate_Add(i, Item);
			break;
		}
	}
}

void UInventoryComponent::AddItemToEquip(FString EquipSlot,class ABaseItem* NewItem)
{
	AEquipItem* EquipItem = Cast<AEquipItem>(NewItem);
	if(EquipItem)
	{
		_EquipSlots.Add(EquipSlot,EquipItem);
		_EquipSlots[EquipSlot]->UseItem();
		UIupdate_equip(EquipSlot, _EquipSlots[EquipSlot]);
	}
	
}

void UInventoryComponent::ShowItemSlots()
{
	for (int32 i = 0; i < _ItemSlots.Num(); i++)
	{
		ABaseItem *Item = _ItemSlots[i];
		if (Item)
		{
			UE_LOG(LogTemp, Warning, TEXT("Slot %d: %s"), i, *Item->GetName());
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Slot %d: Empty"), i);
		}
	}

	for (const auto &Item : _EquipSlots)
	{
		if (Item.Value)
		{
			UE_LOG(LogTemp, Warning, TEXT("EquipSlot %s: %s"), *Item.Key, *Item.Value->GetName());
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("EquipSlot %s: Empty"), *Item.Key);
		}
	}
}

void UInventoryComponent::GettingMoney(int32 amount)
{
	_Wallet += amount;

	UIManager->GetInventoryUI()->UpdateGold(_Wallet);
}

void UInventoryComponent::UpdateUI()
{
	for (int32 i = 0; i < _itemSlotMax; i++)
	{
		if (_ItemSlots.IsValidIndex(i) && _ItemSlots[i] != nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("updateUi itemslot : %d"), i);
			UIupdate_Add(i, _ItemSlots[i]);
		}
	}

	for (int32 emptySlot : _EmptySlots)
	{
		if (_ItemSlots.IsValidIndex(emptySlot))
		{
			UIupdate_Pop(emptySlot);
		}
	}

	for (const auto& EquipSlot : _EquipSlots)
    {
        FString SlotName = EquipSlot.Key;
        AEquipItem* EquipItem = EquipSlot.Value;
        
        if (EquipItem != nullptr)
        {
            UE_LOG(LogTemp, Warning, TEXT("updateUi equip slot : %s"), *SlotName);
            UIupdate_equip(SlotName, EquipItem);
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("updateUi equip slot : %s is empty"), *SlotName);
            UIupdate_equip(SlotName, nullptr);
        }
    }


}


void UInventoryComponent::SetMoney(int32 amount)
{
	_Wallet = amount;
	UIManager->GetInventoryUI()->UpdateGold(_Wallet);
}
