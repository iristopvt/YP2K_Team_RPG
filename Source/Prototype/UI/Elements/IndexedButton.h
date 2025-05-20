// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Button.h"
#include "IndexedButton.generated.h"

class ABaseItem;
class UTexture2D;

UENUM()
enum class SlotType : uint8
{
	Inventory = 0,
	Equip
};

UCLASS()
class PROTOTYPE_API UIndexedButton : public UButton
{
	GENERATED_BODY()
	
public:
	int32 GetIndex() { return _index; }
	ABaseItem* GetItem() { return _item; }
	UTexture2D* GetImage() { return _image; }
	SlotType GetSlotType() { return _slotType; }

	void SetIndex(int32 index) { _index = index; }
	void SetItem(ABaseItem* item) { _item = item; }
	void SetImage(UTexture2D* image) { _image = image; }
	void SetSlotType(SlotType type) { _slotType = type; }

	void ButtonUpdate();

private:
	UPROPERTY(meta = (BindWidget))
	UTexture2D* _image;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32 _index;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	ABaseItem* _item;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	SlotType _slotType;
};
