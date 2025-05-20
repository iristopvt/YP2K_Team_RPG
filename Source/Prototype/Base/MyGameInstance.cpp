// Fill out your copyright notice in the Description page of Project Settings.
#include "Base/MyGameInstance.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Component/StatComponent.h"
#include "Component/InventoryComponent.h"
#include "Player/MyPlayer.h"
#include "Item/BaseItem.h"
#include "Item/Equip/EquipItem.h"
#include "Item/Consumes/ConsumeItem.h"
#include "../UI/InventoryWidget.h"
#include "../Item/BaseItem.h"
#include "../Item/Equip/EquipItem.h"
#include "../Component/InventoryComponent.h"
#include "Base/Managers/UIManager.h"
#include "Base/Managers/SoundManager.h"

UMyGameInstance::UMyGameInstance()
{
	static ConstructorHelpers::FObjectFinder<UDataTable> StatData(TEXT("/Script/Engine.DataTable'/Game/Data/StatDataTable.StatDataTable'"));

	if (StatData.Succeeded())
	{
		_statTable = StatData.Object;
	}

	// 현재 에픽 스탯데이터테이블 까지완
	static ConstructorHelpers::FObjectFinder<UDataTable> EpicStatData(TEXT("/Script/Engine.DataTable'/Game/Data/EpicMonsterDataTable.EpicMonsterDataTable'"));

	if (EpicStatData.Succeeded())
	{
		_EpicstatTable = EpicStatData.Object;
	}

	static ConstructorHelpers::FObjectFinder<UDataTable> MonsterStatData(TEXT("/Script/Engine.DataTable'/Game/Data/NormalMonsterDataTable.NormalMonsterDataTable'"));

	if (MonsterStatData.Succeeded())
	{
		_MonsterstatTable = MonsterStatData.Object;
	}

	static ConstructorHelpers::FObjectFinder<UDataTable> BossStatData(TEXT("/Script/Engine.DataTable'/Game/Data/BossMonsterDataTable.BossMonsterDataTable'"));

	if (BossStatData.Succeeded())
	{
		_BossstatTable = BossStatData.Object;
	}

	static ConstructorHelpers::FObjectFinder<UDataTable> ConsumItemData(TEXT("/Script/Engine.DataTable'/Game/Data/Item/ConsumeItem.ConsumeItem'"));

	if (ConsumItemData.Succeeded())
	{
		_ConsItemTable = ConsumItemData.Object;
	}

	static ConstructorHelpers::FObjectFinder<UDataTable> EquipItemData(TEXT("/Script/Engine.DataTable'/Game/Data/Item/Equipitem.Equipitem'"));

	if (EquipItemData.Succeeded())
	{
		_EquipItemTable = EquipItemData.Object;
	}

	static ConstructorHelpers::FObjectFinder<UDataTable> DragonStat(TEXT("/Script/Engine.DataTable'/Game/Data/DragonStatDataTable.DragonStatDataTable'"));

	if (DragonStat.Succeeded())
	{
		_DragonStatTable = DragonStat.Object;
	}
	
	static ConstructorHelpers::FObjectFinder<UDataTable> shopList1(TEXT("/Script/Engine.DataTable'/Game/Data/Postion_ShopKeeper.Postion_ShopKeeper'"));
	if (shopList1.Succeeded())
	{
		_ShopLists.Add(shopList1.Object);
	}
	static ConstructorHelpers::FObjectFinder<UDataTable> shopList2(TEXT("/Script/Engine.DataTable'/Game/Data/BasicEquip_ShopKeeper.BasicEquip_ShopKeeper'"));
	if (shopList2.Succeeded())
	{
		_ShopLists.Add(shopList2.Object);
	}
	static ConstructorHelpers::FObjectFinder<UDataTable> shopList3(TEXT("/Script/Engine.DataTable'/Game/Data/ShinyEquip_ShopKeeper.ShinyEquip_ShopKeeper'"));
	if (shopList3.Succeeded())
	{
		_ShopLists.Add(shopList3.Object);
	}
	static ConstructorHelpers::FObjectFinder<UDataTable> shopList4(TEXT("/Script/Engine.DataTable'/Game/Data/ShadowEquip_ShopKeeper.ShadowEquip_ShopKeeper'"));
	if (shopList4.Succeeded())
	{
		_ShopLists.Add(shopList4.Object);
	}
}

void UMyGameInstance::SavePlayerStats(class UStatComponent *StatComponent)
{
	if (StatComponent)
	{
		_savedLevel = StatComponent->GetLevel();
		_savedMaxHp = StatComponent->GetMaxHp();
		_savedOgHp = StatComponent->GetOgHp();
		_savedMaxMp = StatComponent->GetMaxMp();
		_savedOgMp = StatComponent->GetOhMp();
		_savedStr = StatComponent->GetStr();
		_savedOgStr = StatComponent->GetOgStr();
		_savedModStr = StatComponent->GetModStr();
		
		_savedDex = StatComponent->GetDex();
		_savedOgDex = StatComponent->GetOgDex();
		_savedModDex = StatComponent->GetModDex();

		_savedInt = StatComponent->GetInt();
		_savedOgInt = StatComponent->GetOgInt();
		_savedModInt = StatComponent->GetModInt();

		_savedAttackRadius = StatComponent->GetAttackRadius();
		_savedAttackRange = StatComponent->GetAttackRange();

		_savedCurHp = StatComponent->GetCurHp();
		_savedCurMp = StatComponent->GetCurMp();
		_savedExp = StatComponent->GetExp();
		_savedNextExp = StatComponent->GetNextExp();
		_savedBonus = StatComponent->GetBonusPoint();
	}
}

void UMyGameInstance::LoadPlayerStats(class UStatComponent *StatComponent)
{
	if (StatComponent)
	{
		StatComponent->SetLevel(_savedLevel);
		StatComponent->SetMaxHp(_savedMaxHp);
		StatComponent->SetOgHp(_savedOgHp);
		StatComponent->SetMaxMp(_savedMaxMp);
		StatComponent->SetOgMp(_savedOgMp);
		StatComponent->SetStr(_savedStr);
		StatComponent->SetOgStr(_savedOgStr);
		StatComponent->SetModStr(_savedModStr);

		StatComponent->SetDex(_savedDex);
		StatComponent->SetOgDex(_savedOgDex);
		StatComponent->SetModDex(_savedModDex);

		StatComponent->SetInt(_savedInt);
		StatComponent->SetOgInt(_savedOgInt);
		StatComponent->SetModInt(_savedModInt);

		StatComponent->SetAttackRange(_savedAttackRange);
		StatComponent->SetAttackRadius(_savedAttackRadius);

		StatComponent->SetHp(_savedCurHp);
		StatComponent->SetMp(_savedCurMp);
		StatComponent->SetNextExp(_savedNextExp);
		StatComponent->SetBonusPoint(_savedBonus);
		StatComponent->AddExp(_savedExp);

		StatComponent->UpdateUI();
	}
}


void UMyGameInstance::SaveInventory(class UInventoryComponent *InventoryComponent)
{
	if (InventoryComponent)
	{
		SavedInventoryData.Empty();
		SavedEquipData.Empty();
		
		TArray<ABaseItem *> Items = InventoryComponent->GetItemSlots();
		TMap<FString, AEquipItem *> EquipItems = InventoryComponent->GetEquipSlots();

		for (ABaseItem *Item : Items)
		{
			if (Item)
			{
				FItemData ItemData;
				ItemData._Code = Item->GetCode();
				ItemData._Name = Item->GetName();
				ItemData._Type = Item->GetType();
				ItemData._ModTarget = Item->GetModStat();
				ItemData._Description = Item->GetDesc();
				ItemData._Price = Item->GetPrice();
				ItemData._Value = Item->GetValue();
				ItemData._Mesh = Item->GetSkeletalMesh();
				ItemData._Texture = Item->GetTexture();
				ItemData._Equip = Item->GetEquip();

				SavedInventoryData.Add(ItemData);
			}
		}

		for (auto &Item : EquipItems)
		{
			if (Item.Value)
			{
				FItemData ItemData;
				ItemData._Code = Item.Value->GetCode();
				ItemData._Name = Item.Value->GetName();
				ItemData._Type = Item.Value->GetType();
				ItemData._ModTarget = Item.Value->GetModStat();
				ItemData._Description = Item.Value->GetDesc();
				ItemData._Price = Item.Value->GetPrice();
				ItemData._Value = Item.Value->GetValue();
				ItemData._Mesh = Item.Value->GetSkeletalMesh();
				ItemData._Texture = Item.Value->GetTexture();
				ItemData._Equip = static_cast<int>(Item.Value->GetEquipType());
				
				SavedEquipData.Add(Item.Key, ItemData);
			}
		}
		_savedMoney = InventoryComponent->GetHowMuchIHave();

	}
}

void UMyGameInstance::LoadInventory(class UInventoryComponent *InventoryComponent)
{
	if (InventoryComponent)
	{
		InventoryComponent->InitSlot();

		for (const FItemData &ItemData : SavedInventoryData)
		{
			ABaseItem *NewItem = nullptr;

			if (ItemData._Type == ItemType::Consume)
			{
				NewItem = GetWorld()->SpawnActor<AConsumeItem>(AConsumeItem::StaticClass(), FVector::ZeroVector, FRotator::ZeroRotator);
				NewItem->SetItemWithCode(ItemData._Code);
			}
			else if (ItemData._Type == ItemType::Equipment)
			{
				AEquipItem *EquipItem = GetWorld()->SpawnActor<AEquipItem>(AEquipItem::StaticClass(), FVector::ZeroVector, FRotator::ZeroRotator);
				EquipItem->SetItemWithCode(ItemData._Code);
				EquipItem->SetEquipType(ItemData._Equip);
				NewItem = EquipItem;
			}

			if (NewItem)
			{
				InventoryComponent->AddItemToSlot(NewItem);
			}
		}
		
		for (const auto &Item : SavedEquipData)
		{
			AEquipItem *NewItem = nullptr;
			FString EquipType = Item.Key;
			const FItemData &ItemData = Item.Value;

			if (ItemData._Type == ItemType::Equipment)
			{
				AEquipItem* EquipItem = GetWorld()->SpawnActor<AEquipItem>(AEquipItem::StaticClass(), FVector::ZeroVector, FRotator::ZeroRotator);
				if (EquipItem)
				{
					EquipItem->SetItemWithCode(ItemData._Code);
					EquipItem->SetEquipType(ItemData._Equip);
					NewItem = EquipItem;

                    InventoryComponent->AddItemToEquip(EquipType,NewItem);
				}
			} 
		}
		InventoryComponent->GettingMoney(_savedMoney);
	}
}

void UMyGameInstance::SavePlayerSkeletal(class AMyPlayer* player)
{
    if (player)
    {
		_savedBodyMesh = player->GetMesh() ? Cast<USkeletalMesh>(player->GetMesh()->GetSkinnedAsset()) : nullptr;
		_savedLowerBodyMesh = player->_lowerBodyMesh ? Cast<USkeletalMesh>(player->_lowerBodyMesh->GetSkinnedAsset()) : nullptr;
		_savedShoulderBodyMesh = player->_shoulderBodyMesh ? Cast<USkeletalMesh>(player->_shoulderBodyMesh->GetSkinnedAsset()) : nullptr;
		_savedSwordBodyMesh = player->_swordBodyMesh ? Cast<USkeletalMesh>(player->_swordBodyMesh->GetSkinnedAsset()) : nullptr;
		_savedShieldBodyMesh = player->_shieldBodyMesh ? Cast<USkeletalMesh>(player->_shieldBodyMesh->GetSkinnedAsset()) : nullptr;
    }
}

void UMyGameInstance::LoadPlayerSkeletal(class AMyPlayer* player)
{
    if (player)
    {
        if (_savedBodyMesh && player->GetMesh())
        {
            player->GetMesh()->SetSkeletalMesh(_savedBodyMesh);
        }

        if (_savedLowerBodyMesh && player->_lowerBodyMesh)
        {
            player->_lowerBodyMesh->SetSkeletalMesh(_savedLowerBodyMesh);
        }

        if (_savedShoulderBodyMesh && player->_shoulderBodyMesh)
        {
            player->_shoulderBodyMesh->SetSkeletalMesh(_savedShoulderBodyMesh);
        }

        if (_savedSwordBodyMesh && player->_swordBodyMesh)
        {
            player->_swordBodyMesh->SetSkeletalMesh(_savedSwordBodyMesh);
        }

        if (_savedShieldBodyMesh && player->_shieldBodyMesh)
        {
            player->_shieldBodyMesh->SetSkeletalMesh(_savedShieldBodyMesh);
        }
    }
}

TArray<ABaseItem*> UMyGameInstance::GetInvenItemList()
{
	return UIManager->GetInventoryUI()->GetInvenContents();
}

void UMyGameInstance::Init()
{
	Super::Init();

	auto statData = GetStatDataByLevel(1);
	auto EpicData = GetEpicDataByLevel(1);
	auto BossData = GetBossDataByLevel(1);
	auto MonsterData = GetMonsterDataByLevel(1);

	InitializeManagers();
}

void UMyGameInstance::InitializeManagers()
{
	FActorSpawnParameters params;
	params.Name = TEXT("UIManager");
	_UIManager = GetWorld()->SpawnActor<AUIManager>(FVector::ZeroVector, FRotator::ZeroRotator, params);

	FActorSpawnParameters soundParams;
	soundParams.Name = TEXT("SoundManager");
	_soundManager = GetWorld()->SpawnActor<ASoundManager>(FVector::ZeroVector, FRotator::ZeroRotator, soundParams);

	FActorSpawnParameters effectParams;
	effectParams.Name = TEXT("EffectManager");
	_effectManager = GetWorld()->SpawnActor<AEffectManager>(FVector::ZeroVector, FRotator::ZeroRotator, effectParams);
}

FMyStatData *UMyGameInstance::GetStatDataByLevel(int level)
{
	auto statData = _statTable->FindRow<FMyStatData>(*FString::FromInt(level), TEXT(""));
	return statData;
}

FMyStatData* UMyGameInstance::GetMonsterDataByLevel(int level)
{
	auto MonsterData = _MonsterstatTable->FindRow<FMyStatData>(*FString::FromInt(level), TEXT(""));
	return MonsterData;
}

FMyStatData *UMyGameInstance::GetEpicDataByLevel(int level)
{
	auto EpicStatData = _EpicstatTable->FindRow<FMyStatData>(*FString::FromInt(level), TEXT(""));
	return EpicStatData;
}

FMyStatData *UMyGameInstance::GetBossDataByLevel(int level)
{
	auto BossStatData = _BossstatTable->FindRow<FMyStatData>(*FString::FromInt(level), TEXT(""));
	return BossStatData;
}

FMyStatData* UMyGameInstance::GetDragonDataByLevel(int level)
{
	auto DragonStatData = _DragonStatTable->FindRow<FMyStatData>(*FString::FromInt(level), TEXT(""));
	return DragonStatData;
}

FItemData *UMyGameInstance::GetConsumeItemData(int code)
{
	auto ConsumeData = _ConsItemTable->FindRow<FItemData>(*FString::FromInt(code), TEXT(""));
	return ConsumeData;
}

FItemData *UMyGameInstance::GetEquipItemData(int code)
{
	auto EquipData = _EquipItemTable->FindRow<FItemData>(*FString::FromInt(code), TEXT(""));
	return EquipData;
}

TArray<FSellings*> UMyGameInstance::GetSellingData(int32 shop)
{
	TArray<FSellings*> sellingList;
	FSellings* sellingData = nullptr;
	
	for (int i = 0; i < SHOP_LIST_MAX; i++)
	{
		sellingData = _ShopLists[shop]->FindRow<FSellings>(*FString::FromInt(i), TEXT(""));
		sellingList.Add(sellingData);
	}

	return sellingList;
}

ABaseItem* UMyGameInstance::SellDataToItemData(FSellings* data)
{
	if (data->Type == ItemType::Equipment)
	{
		AEquipItem* equip = GetWorld()->SpawnActor<AEquipItem>(AEquipItem::StaticClass(), FVector::ZeroVector, FRotator::ZeroRotator);
		equip->SetItemWithCode(data->Code);
		return Cast<ABaseItem>(equip);
	}
	else
	{
		ABaseItem* consume = GetWorld()->SpawnActor<ABaseItem>(ABaseItem::StaticClass(), FVector::ZeroVector, FRotator::ZeroRotator);
		consume->SetItemWithCode(data->Code);
		return consume;
	}

}
