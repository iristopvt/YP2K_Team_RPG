// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/ShopWidget.h"
#include "Base/MyGameInstance.h"
#include "Base/Managers/UIManager.h"
#include "Player/MyPlayer.h"
#include "Components/UniformGridPanel.h"
#include "InventoryWidget.h"
#include "Component/InventoryComponent.h"
#include "Component/ShopComponent.h"
#include "Components/CanvasPanel.h"
#include "UI/Elements/IndexedButton.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"

bool UShopWidget::Initialize()
{
	bool result = Super::Initialize();

	SetInvenButtons();

	_SellPanels.Add(SellPanel_0);
	_SellPanels.Add(SellPanel_1);
	_SellPanels.Add(SellPanel_2);
	_SellPanels.Add(SellPanel_3);
	_SellPanels.Add(SellPanel_4);

	Cast<UButton>(_SellPanels[0]->GetChildAt(4))->OnClicked.AddDynamic(this, &UShopWidget::BuySlot1);
	Cast<UButton>(_SellPanels[1]->GetChildAt(4))->OnClicked.AddDynamic(this, &UShopWidget::BuySlot2);
	Cast<UButton>(_SellPanels[2]->GetChildAt(4))->OnClicked.AddDynamic(this, &UShopWidget::BuySlot3);
	Cast<UButton>(_SellPanels[3]->GetChildAt(4))->OnClicked.AddDynamic(this, &UShopWidget::BuySlot4);
	Cast<UButton>(_SellPanels[4]->GetChildAt(4))->OnClicked.AddDynamic(this, &UShopWidget::BuySlot5);

	Button_[0]->OnClicked.AddDynamic(this, &UShopWidget::TargetItem0);
	Button_[1]->OnClicked.AddDynamic(this, &UShopWidget::TargetItem1);
	Button_[2]->OnClicked.AddDynamic(this, &UShopWidget::TargetItem2);
	Button_[3]->OnClicked.AddDynamic(this, &UShopWidget::TargetItem3);
	Button_[4]->OnClicked.AddDynamic(this, &UShopWidget::TargetItem4);
	Button_[5]->OnClicked.AddDynamic(this, &UShopWidget::TargetItem5);
	Button_[6]->OnClicked.AddDynamic(this, &UShopWidget::TargetItem6);
	Button_[7]->OnClicked.AddDynamic(this, &UShopWidget::TargetItem7);
	Button_[8]->OnClicked.AddDynamic(this, &UShopWidget::TargetItem8);
	Button_[9]->OnClicked.AddDynamic(this, &UShopWidget::TargetItem9);
	Button_[10]->OnClicked.AddDynamic(this, &UShopWidget::TargetItem10);
	Button_[11]->OnClicked.AddDynamic(this, &UShopWidget::TargetItem11);

	SellBtn->OnClicked.AddDynamic(this, &UShopWidget::SellItem);

	_defaultText = TEXT("Item");

	return result;
}

void UShopWidget::UpdateShopList(TArray<ABaseItem*> list)
{
	for (int i = 0; i < list.Num(); i++)
	{
		auto item = Cast<UIndexedButton>(_SellPanels[i]->GetChildAt(0));
		item->SetItem(list[i]);
		item->ButtonUpdate();
		auto name = Cast<UTextBlock>(_SellPanels[i]->GetChildAt(1));
		name->SetText(FText::FromString(list[i]->GetName()));
		auto price = Cast<UTextBlock>(_SellPanels[i]->GetChildAt(2));
		price->SetText(FText::FromString(FString::FromInt(list[i]->GetPrice()) + FString(TEXT(" G"))));
		auto description = Cast<UTextBlock>(_SellPanels[i]->GetChildAt(3));
		description->SetText(FText::FromString(list[i]->GetDesc()));
	}
}

void UShopWidget::ReflectInvenSlots(AMyPlayer* player)
{
	_isSlotFull = true;
	TArray<ABaseItem*> itemList = player->_inventoryComponent->GetItemSlots();
	for (int i = 0; i < Button_.Num(); i++)
	{
		Button_[i]->SetItem(itemList[i]);
		Button_[i]->ButtonUpdate();
		if (_isSlotFull && itemList[i] == nullptr)
			_isSlotFull = false;
	}

	//TODO : Get Wallet too & Call this every opening
	int32 Gold = player->_inventoryComponent->GetHowMuchIHave();
	p_gold = Gold;
	GoldAmount->SetText(FText::FromString(FString::FromInt(Gold)));
}

void UShopWidget::SetInvenButtons()
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
}

DealContext UShopWidget::BuyResult(int32 slot)
{
	if (slot >= _SellPanels.Num())
		return DealContext::Error;

	auto item = Cast<UIndexedButton>(_SellPanels[slot]->GetChildAt(0))->GetItem();

	if (item == nullptr)
		return DealContext::EmptySlot;
	if (p_gold < item->GetPrice())
		return DealContext::MoneyNotEnough;
	if (_isSlotFull)
		return DealContext::InventoryIsFull;

	return DealContext::Succeed;
}

void UShopWidget::TryBuyItem(int32 slot)
{
	auto result = BuyResult(slot);
	switch (result)
	{
	case DealContext::Error:
		UE_LOG(LogTemp, Error, TEXT("Item Buy Error!"));
		break;
	case DealContext::Succeed:
		BuySucceed.Broadcast(slot);
		break;
	case DealContext::MoneyNotEnough:
		UE_LOG(LogTemp, Warning, TEXT("Doenst have enough money"));
		break;
	case DealContext::InventoryIsFull:
		UE_LOG(LogTemp, Warning, TEXT("Inventory is full!!"));
		break;
	case DealContext::EmptySlot:
		UE_LOG(LogTemp, Warning, TEXT("You cant buy Air"));
		break;
	default:
		break;
	}
}

void UShopWidget::SellItem()
{
	if (_targetItem == nullptr)
		return;
	if (_targetIndex == -1)
		return;

	SaleItem.Broadcast(_targetIndex, _tempPrice);
	_targetItem = nullptr;
	_targetIndex = -1;
	_tempPrice = 0;
	ShowItem();
}

void UShopWidget::BuySlot1()
{
	TryBuyItem(0);
}

void UShopWidget::BuySlot2()
{
	TryBuyItem(1);
}

void UShopWidget::BuySlot3()
{
	TryBuyItem(2);
}

void UShopWidget::BuySlot4()
{
	TryBuyItem(3);
}

void UShopWidget::BuySlot5()
{
	TryBuyItem(4);
}

void UShopWidget::ShowItem()
{
	if (_targetItem == nullptr)
	{
		ItemTexture->SetBrushFromTexture(T_DEFAULT);
		ItemName->SetText(FText::FromString(_defaultText));
		Price->SetText(FText::FromString(TEXT("00 G")));
	}
	else
	{
		ItemTexture->SetBrushFromTexture(_targetItem->GetTexture());
		ItemName->SetText(FText::FromString(_targetItem->GetName()));
		_tempPrice = _targetItem->GetPrice() * SellDCAmount;
		Price->SetText(FText::FromString(FString::FromInt(_tempPrice) + FString(TEXT(" G"))));
	}
}

void UShopWidget::SetTargetItem(int32 slotIndex)
{
	if (Button_[slotIndex] == nullptr)
		return;

	ABaseItem* item = Button_[slotIndex]->GetItem();
	if (item == nullptr) return;

	_targetItem = item;
	_targetIndex = slotIndex;
	ShowItem();
}

void UShopWidget::TargetItem0()
{
	SetTargetItem(0);
}

void UShopWidget::TargetItem1()
{
	SetTargetItem(1);
}

void UShopWidget::TargetItem2()
{
	SetTargetItem(2);
}

void UShopWidget::TargetItem3()
{
	SetTargetItem(3);
}

void UShopWidget::TargetItem4()
{
	SetTargetItem(4);
}

void UShopWidget::TargetItem5()
{
	SetTargetItem(5);
}

void UShopWidget::TargetItem6()
{
	SetTargetItem(6);
}

void UShopWidget::TargetItem7()
{
	SetTargetItem(7);
}

void UShopWidget::TargetItem8()
{
	SetTargetItem(8);
}

void UShopWidget::TargetItem9()
{
	SetTargetItem(9);
}

void UShopWidget::TargetItem10()
{
	SetTargetItem(10);
}

void UShopWidget::TargetItem11()
{
	SetTargetItem(11);
}
