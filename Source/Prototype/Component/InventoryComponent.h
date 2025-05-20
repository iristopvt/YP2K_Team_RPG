// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"

class ABaseItem;
class UInventoryWidget;
enum class EItemType : uint8;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROTOTYPE_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventoryComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	void InitSlot();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void AddItem(int32 slot = 0, ABaseItem* item = nullptr);
	virtual void InitializeComponent() override;
	void AddItemToSlot(class ABaseItem* Item);
	void AddItemToEquip(FString EquipSlot, class ABaseItem* NewItem);
	

	void ShowItemSlots();


	UFUNCTION()
	void ExcuteItem(int32 slot, bool isDrop);
	void DeleteItem(int32 slot);
	void ExcuteEquip(FString part);
	void EquipItem(int32 slot);
	void TryEquip(FString part, int32 slot);
	void StripEquip(FString part);

	void UIupdate_Add(int32 slot, ABaseItem* item);
	void UIupdate_Pop(int32 slot);
	void UIupdate_Pop(FString part);
	void UIupdate_equip(FString slot, ABaseItem* item);

	TArray<ABaseItem*> GetItemSlots(){return _ItemSlots;}
	TMap<FString, class AEquipItem*> GetEquipSlots(){return _EquipSlots;}

	int32 GetHowMuchIHave() { return _Wallet; }
	void GettingMoney(int32 amount);
	void SetMoney(int32 amount);

	void UpdateUI();

	bool IsSlotFull() { return _isSlotFull; }

private:
	//Trigger
	bool _isSlotFull = false;
	int32 _itemSlotMax = 12;
	int32 _equipSlotMax = 6;

	void SlotFullCheck();
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Inventory, meta = (AllowPrivateAccess = "true"))
	TArray<ABaseItem*> _ItemSlots;

	TArray<int32> _EmptySlots;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Inventory, meta = (AllowPrivateAccess = "true"))
	TMap<FString, class AEquipItem*> _EquipSlots;

	int32 _Wallet = 0;
};
