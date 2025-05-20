// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InventoryWidget.h"

#include "Base/MyGameInstance.h"
#include "Base/Managers/UIManager.h"
#include "Components/UniformGridPanel.h"
#include "Components/Widget.h"
#include "Components/Button.h"
#include "UI/Elements/IndexedButton.h"
#include "Components/Image.h"
#include "Components/PanelWidget.h"
#include "Components/TextBlock.h"

#include "Item/BaseItem.h"
#include "Item/Consumes/ConsumeItem.h"
#include "Item/Equip/EquipItem.h"
#include "Component/StatComponent.h"

UInventoryWidget::UInventoryWidget(const FObjectInitializer& ObjectInitializer)
	: UUserWidget(ObjectInitializer)
{
}

bool UInventoryWidget::Initialize()
{
	bool result = Super::Initialize();

	SetItemButtons();
	SetStats();

	Button_[0]->OnClicked.AddDynamic(this, &UInventoryWidget::TargetItem0);
	Button_[1]->OnClicked.AddDynamic(this, &UInventoryWidget::TargetItem1);
	Button_[2]->OnClicked.AddDynamic(this, &UInventoryWidget::TargetItem2);
	Button_[3]->OnClicked.AddDynamic(this, &UInventoryWidget::TargetItem3);
	Button_[4]->OnClicked.AddDynamic(this, &UInventoryWidget::TargetItem4);
	Button_[5]->OnClicked.AddDynamic(this, &UInventoryWidget::TargetItem5);
	Button_[6]->OnClicked.AddDynamic(this, &UInventoryWidget::TargetItem6);
	Button_[7]->OnClicked.AddDynamic(this, &UInventoryWidget::TargetItem7);
	Button_[8]->OnClicked.AddDynamic(this, &UInventoryWidget::TargetItem8);
	Button_[9]->OnClicked.AddDynamic(this, &UInventoryWidget::TargetItem9);
	Button_[10]->OnClicked.AddDynamic(this, &UInventoryWidget::TargetItem10);
	Button_[11]->OnClicked.AddDynamic(this, &UInventoryWidget::TargetItem11);

	Helmet->OnClicked.AddDynamic(this, &UInventoryWidget::TargetHemet);
	ShoulderGuard->OnClicked.AddDynamic(this, &UInventoryWidget::TargetShoulder);
	UpperArmor->OnClicked.AddDynamic(this, &UInventoryWidget::TargetUpper);
	LowerArmor->OnClicked.AddDynamic(this, &UInventoryWidget::TargetLower);
	Sword->OnClicked.AddDynamic(this, &UInventoryWidget::TargetSword);
	Shield->OnClicked.AddDynamic(this, &UInventoryWidget::TargetShield);

	DropBtn->OnClicked.AddDynamic(this, &UInventoryWidget::DropItem);
	UseBtn->OnClicked.AddDynamic(this, &UInventoryWidget::UseItem);

	_VogStat.Reserve(5);

	return result;
}

void UInventoryWidget::SetItemButtons()
{
	TArray<UWidget*> widgets;
	widgets = ItemSlots->GetAllChildren();

	int32 index = 0;
	for (UWidget* widget : widgets)
	{
		UIndexedButton* button = Cast<UIndexedButton>(widget);
		if (button)
		{
			button->SetIndex(index);
			button->SetSlotType(SlotType::Inventory);
			button->SetIsEnabled(true);
			Button_.Add(button);

			index++;
		}
	}
	Helmet->SetSlotType(SlotType::Equip);
	ShoulderGuard->SetSlotType(SlotType::Equip);
	UpperArmor->SetSlotType(SlotType::Equip);
	LowerArmor->SetSlotType(SlotType::Equip);
	Sword->SetSlotType(SlotType::Equip);
	Shield->SetSlotType(SlotType::Equip);

	_EquipSlots.Add(Helmet);
	_EquipSlots.Add(ShoulderGuard);
	_EquipSlots.Add(UpperArmor);
	_EquipSlots.Add(LowerArmor);
	_EquipSlots.Add(Sword);
	_EquipSlots.Add(Shield);
}

void UInventoryWidget::SetStats()
{
	TArray<UWidget*> widgets;
	widgets = StatSlots->GetAllChildren();

	for (int i = 5; i < 10; i++)
	{
		UTextBlock* textblock = Cast<UTextBlock>(widgets[i]);
		_originStat.Add(textblock);
	}
	for (int i = 15; i < widgets.Num(); i++)
	{
		UTextBlock* textblock = Cast<UTextBlock>(widgets[i]);
		_modStat.Add(textblock);
	}
}

void UInventoryWidget::UpdateItemSlot(int32 slotIndex, ABaseItem* item)
{
	Button_[slotIndex]->SetItem(item);
	Button_[slotIndex]->ButtonUpdate();
}

void UInventoryWidget::UpdateAllEquipBtn()
{
	Helmet->ButtonUpdate();
	ShoulderGuard->ButtonUpdate();
	UpperArmor->ButtonUpdate();
	LowerArmor->ButtonUpdate();
	Sword->ButtonUpdate();
	Shield->ButtonUpdate();
}

void UInventoryWidget::UpdateEquipSlot(FString slot, ABaseItem* item)
{
	if (item)
    {
        UE_LOG(LogTemp, Warning, TEXT("UpdateEquipSlot: %s - Item: %s"), *slot, *item->GetName());
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("UpdateEquipSlot: %s - Item: None"), *slot);
    }
	
    if (slot == TEXT("Helmet"))
    {
        Helmet->SetItem(item);
		Helmet->ButtonUpdate();
    }
    else if (slot == TEXT("UpperArmor"))
    {
        UpperArmor->SetItem(item);
		UpperArmor->ButtonUpdate();
    }
    else if (slot == TEXT("ShoulderArmor"))
    {
        ShoulderGuard->SetItem(item);
		ShoulderGuard->ButtonUpdate();
    }
    else if (slot == TEXT("LowerArmor"))
    {
        LowerArmor->SetItem(item);
		LowerArmor->ButtonUpdate();
    }
    else if (slot == TEXT("Sword"))
    {
        Sword->SetItem(item);
		Sword->ButtonUpdate();
    }
    else if (slot == TEXT("Shield"))
    {
        Shield->SetItem(item);
		Shield->ButtonUpdate();
    }
    
}

void UInventoryWidget::ShowItem()
{
	UpdateStat();
	if (_targetItem == nullptr)
	{
		ItemTexture->SetBrushFromTexture(T_DEFAULT);
		ItemName->SetText(FText::FromString(_defaultText));
		ItemDesc->SetText(FText::FromString(_defaultText));
	}
	else
	{
		if (Cast<AEquipItem>(_targetItem))
		{
			if (_targetIndex == -1)
			{
				UseBtnText->SetText(FText::FromString(TEXT("Strip")));
				UpdateModStat((int32)_targetItem->GetModStat(), -_targetItem->GetValue());
			}
			else
			{
				UseBtnText->SetText(FText::FromString(TEXT("Equip")));
				UpdateModStat((int32)_targetItem->GetModStat(), _targetItem->GetValue());
			}
		}
		else
		{
			UseBtnText->SetText(FText::FromString(TEXT("Use")));
		}
		ItemTexture->SetBrushFromTexture(_targetItem->GetTexture());
		ItemName->SetText(FText::FromString(_targetItem->GetName()));
		ItemDesc->SetText(FText::FromString(_targetItem->GetDesc()));
	}
}

void UInventoryWidget::DropItem()
{
	if (_targetItem == nullptr)
		return;
	if (_targetIndex != -1)
		ItemDrop.Broadcast(_targetIndex, true);
	else
	{
		FString part;
		AEquipItem* target = Cast<AEquipItem>(_targetItem);
		switch (target->GetEquipType())
		{
		case EItemType::Helmet:
			part = TEXT("Helmet");
			break;
		case EItemType::UpperArmor:
			part = TEXT("UpperArmor");
			break;
		case EItemType::LowerArmor:
			part = TEXT("LowerArmor");
			break;
		case EItemType::ShoulderArmor:
			part = TEXT("ShoulderArmor");
			break;
		case EItemType::Sword:
			part = TEXT("Sword");
			break;
		case EItemType::Shield:
			part = TEXT("Shield");
			break;
		default:
			break;
		}
		if (!part.IsEmpty())
			EquipDrop.Broadcast(part);
	}

	_targetItem = nullptr;
	ShowItem();
	_targetIndex = -1;
	
}

void UInventoryWidget::UseItem()
{
	if (_targetItem == nullptr)
		return;
	if (_targetItem->GetType() == ItemType::Equipment)
	{
		if (_targetIndex == -1)
		{
			FString part;
			AEquipItem* target = Cast<AEquipItem>(_targetItem);
			switch (target->GetEquipType())
			{
			case EItemType::Helmet:
				UE_LOG(LogTemp, Warning, TEXT("Inventory widget UseItem Halmet"));
				part = TEXT("Helmet");
				break;
			case EItemType::UpperArmor:
				UE_LOG(LogTemp, Warning, TEXT("Inventory widget UseItem Upper"));
				part = TEXT("UpperArmor");
				break;
			case EItemType::LowerArmor:
				UE_LOG(LogTemp, Warning, TEXT("Inventory widget UseItem Lower"));
				part = TEXT("LowerArmor");
				break;
			case EItemType::ShoulderArmor:
				UE_LOG(LogTemp, Warning, TEXT("Inventory widget UseItem Shoulder"));
				part = TEXT("ShoulderArmor");
				break;
			case EItemType::Sword:
				UE_LOG(LogTemp, Warning, TEXT("Inventory widget UseItem Sword"));
				part = TEXT("Sword");
				break;
			case EItemType::Shield:
				UE_LOG(LogTemp, Warning, TEXT("Inventory widget UseItem Shield"));
				part = TEXT("Shield");
				break;
			default:
				UE_LOG(LogTemp, Warning, TEXT("Inventory widget default"));
				break;
			}
			if (!part.IsEmpty())
			{
				EquipStrip.Broadcast(part);
				_targetItem = nullptr;
				UpdateStat();
			}
		}
		else
		{
			CheckCanEquip();
			ItemEquip.Broadcast(_targetIndex);
			UpdateStat();
		}
	}
	else
	{
		ItemDrop.Broadcast(_targetIndex, false);
		ItemUse.Broadcast(_targetIndex);
		_targetItem = nullptr;
	}

	ShowItem();
}

void UInventoryWidget::CheckCanEquip()
{
	AEquipItem* target = Cast<AEquipItem>(_targetItem);

	if (target == nullptr) UE_LOG(LogTemp, Error, TEXT("Equip Missed!"));

	switch (target->GetEquipType())
	{
	case EItemType::Helmet:
		_targetItem = Helmet->GetItem();
		Helmet->SetItem(target);
		break;
	case EItemType::UpperArmor:
		_targetItem = UpperArmor->GetItem();
		UpperArmor->SetItem(target);
		break;
	case EItemType::LowerArmor:
		_targetItem = LowerArmor->GetItem();
		LowerArmor->SetItem(target);
		break;
	case EItemType::ShoulderArmor:
		_targetItem = ShoulderGuard->GetItem();
		ShoulderGuard->SetItem(target);
		break;
	case EItemType::Sword:
		_targetItem = Sword->GetItem();
		Sword->SetItem(target);
		break;
	case EItemType::Shield:
		_targetItem = Shield->GetItem();
		Shield->SetItem(target);
		break;
	default:
		break;
	}

	UpdateAllEquipBtn();
}

void UInventoryWidget::InitStat(TArray<int32> statTable)
{
	if (statTable.Num() < 5)
		return;

	for (int i = 0; i < statTable.Num(); i++)
	{
		_VogStat.Add(statTable[i]);
	}
	for (int i = 0; i < statTable.Num(); i++)
	{
		UpdateOriginStat(i, _VogStat[i]);
	}
	UpdateStat();
}

void UInventoryWidget::UpdateStat()
{
	for (int i = 0; i < 5; i++)
	{
		_modStat[i]->SetText(_originStat[i]->GetText());
		_modStat[i]->SetColorAndOpacity(FSlateColor(FColor(255, 255, 255)));
	}
}

void UInventoryWidget::UpdateOriginStat(int32 statType, int32 amount)
{
	_originStat[statType]->SetText(FText::FromString(FString::FromInt(amount)));
}

void UInventoryWidget::UpdateModStat(int32 statType, int32 amount)
{
	int32 nowStat = FCString::Atoi(*(_originStat[statType]->GetText()).ToString());

	int32 moded = 0;
	if (nowStat == _VogStat[statType] || nowStat + amount == _VogStat[statType])
		moded = nowStat + amount;
	else
		moded = _VogStat[statType] + amount;

	_modStat[statType]->SetText(FText::FromString(FString::FromInt(moded)));

	if (moded > nowStat)
		_modStat[statType]->SetColorAndOpacity(FSlateColor(FColor(0, 200, 0)));
	if (moded == nowStat)
		_modStat[statType]->SetColorAndOpacity(FSlateColor(FColor(255, 255, 255)));
	if (moded < nowStat)
		_modStat[statType]->SetColorAndOpacity(FSlateColor(FColor(150, 0, 0)));
}

void UInventoryWidget::UpdateGold(int32 amount)
{
	GoldAmount->SetText(FText::FromString(FString::FromInt(amount)));
}

TArray<ABaseItem*> UInventoryWidget::GetInvenContents()
{
	TArray<ABaseItem*> ItemList;

	for (auto itemBTN : Button_)
	{
		ItemList.Add(itemBTN->GetItem());
	}
	return ItemList;
}

void UInventoryWidget::SetTargetItem(int32 slotIndex)
{
	if (Button_[slotIndex] == nullptr)
		return;

	ABaseItem* item = Button_[slotIndex]->GetItem();
	if (item == nullptr) return;

	if (_targetItem == item)
		_isThisAlreadyTargetted = true;
	else
		_isThisAlreadyTargetted = false;

	_targetItem = item;
	_targetIndex = slotIndex;
	ShowItem();
}

void UInventoryWidget::SetTargetEquip(EItemType equip)
{
	ABaseItem* item = nullptr;

	switch (equip)
	{
	case EItemType::Helmet:
		item = Helmet->GetItem();
		break;
	case EItemType::UpperArmor:
		item = UpperArmor->GetItem();
		break;
	case EItemType::LowerArmor:
		item = LowerArmor->GetItem();
		break;
	case EItemType::ShoulderArmor:
		item = ShoulderGuard->GetItem();
		break;
	case EItemType::Sword:
		item = Sword->GetItem();
		break;
	case EItemType::Shield:
		item = Shield->GetItem();
		break;
	}
	if (item == nullptr) return;

	if (_targetItem == item)
		_isThisAlreadyTargetted = true;
	else
		_isThisAlreadyTargetted = false;

	_targetItem = item;
	_targetIndex = -1;
	ShowItem();
}

void UInventoryWidget::TargetItem0()
{
	SetTargetItem(0);
}

void UInventoryWidget::TargetItem1()
{
	SetTargetItem(1);
}

void UInventoryWidget::TargetItem2()
{
	SetTargetItem(2);
}

void UInventoryWidget::TargetItem3()
{
	SetTargetItem(3);
}

void UInventoryWidget::TargetItem4()
{
	SetTargetItem(4);
}

void UInventoryWidget::TargetItem5()
{
	SetTargetItem(5);
}

void UInventoryWidget::TargetItem6()
{
	SetTargetItem(6);
}

void UInventoryWidget::TargetItem7()
{
	SetTargetItem(7);
}

void UInventoryWidget::TargetItem8()
{
	SetTargetItem(8);
}

void UInventoryWidget::TargetItem9()
{
	SetTargetItem(9);
}

void UInventoryWidget::TargetItem10()
{
	SetTargetItem(10);
}

void UInventoryWidget::TargetItem11()
{
	SetTargetItem(11);
}

void UInventoryWidget::TargetHemet()
{
	SetTargetEquip(EItemType::Helmet);
}

void UInventoryWidget::TargetShoulder()
{
	SetTargetEquip(EItemType::ShoulderArmor);
}

void UInventoryWidget::TargetUpper()
{
	SetTargetEquip(EItemType::UpperArmor);
}

void UInventoryWidget::TargetLower()
{
	SetTargetEquip(EItemType::LowerArmor);
}

void UInventoryWidget::TargetSword()
{
	SetTargetEquip(EItemType::Sword);
}

void UInventoryWidget::TargetShield()
{
	SetTargetEquip(EItemType::Shield);
}
