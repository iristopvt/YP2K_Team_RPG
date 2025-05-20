// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ShopWidget.generated.h"

class UCanvasPanel;
class ABaseItem;
class UIndexedButton;

#define SellDCAmount 0.6f

UENUM()
enum class DealContext
{
	Error = -1,
	Succeed = 0,
	MoneyNotEnough,
	InventoryIsFull,
	EmptySlot,
};

DECLARE_MULTICAST_DELEGATE_OneParam(ItemBuy, int32);
DECLARE_MULTICAST_DELEGATE_TwoParams(ItemSale, int32, int32);

UCLASS()
class PROTOTYPE_API UShopWidget : public UUserWidget
{
	GENERATED_BODY()
	
	virtual bool Initialize() override;

public:
	void UpdateShopList(TArray<ABaseItem*> list);
	void ReflectInvenSlots(class AMyPlayer* player);

	ItemBuy BuySucceed;
	ItemSale SaleItem;
private:
	
	void SetInvenButtons();

	DealContext BuyResult(int32 slot);
	void TryBuyItem(int32 slot);
	UFUNCTION()
	void SellItem();

	UFUNCTION()
	void BuySlot1();
	UFUNCTION()
	void BuySlot2();
	UFUNCTION()
	void BuySlot3();
	UFUNCTION()
	void BuySlot4();
	UFUNCTION()
	void BuySlot5();

	void ShowItem();
	void SetTargetItem(int32 slotIndex);

	UFUNCTION()
	void TargetItem0();
	UFUNCTION()
	void TargetItem1();
	UFUNCTION()
	void TargetItem2();
	UFUNCTION()
	void TargetItem3();
	UFUNCTION()
	void TargetItem4();
	UFUNCTION()
	void TargetItem5();
	UFUNCTION()
	void TargetItem6();
	UFUNCTION()
	void TargetItem7();
	UFUNCTION()
	void TargetItem8();
	UFUNCTION()
	void TargetItem9();
	UFUNCTION()
	void TargetItem10();
	UFUNCTION()
	void TargetItem11();

	/// <summary>
	/// Inventory Elements
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Texture, meta = (AllowPrivateAccess = "true"))
	FString _defaultText;

	UPROPERTY()
	ABaseItem* _targetItem = nullptr;
	UPROPERTY()
	int32 _targetIndex = -1;

	//UI Elememts
	UPROPERTY(meta = (BindWidget))
	class UUniformGridPanel* ItemSlots;
	UPROPERTY(meta = (BindWidget))
	TArray<UIndexedButton*> Button_;
	bool _isSlotFull = true;

	UPROPERTY(meta = (BindWidget))
	class UImage* ItemTexture;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* ItemName;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Price;

	UPROPERTY(meta = (BindWidget))
	class UButton* SellBtn;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* SellBtnText;
	
	int32 p_gold;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* GoldAmount;

	//////////////////////////////////
	///Shop Elements

	TArray<UCanvasPanel*> _SellPanels;

	UPROPERTY(meta = (BindWidget))
	UCanvasPanel* SellPanel_0;
	
	UPROPERTY(meta = (BindWidget))
	UCanvasPanel* SellPanel_1;
	
	UPROPERTY(meta = (BindWidget))
	UCanvasPanel* SellPanel_2;
	
	UPROPERTY(meta = (BindWidget))
	UCanvasPanel* SellPanel_3;
	
	UPROPERTY(meta = (BindWidget))
	UCanvasPanel* SellPanel_4;

	int32 _tempPrice;

};
