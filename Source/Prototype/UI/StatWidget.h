// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "../Component/StatComponent.h"
#include "StatWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROTOTYPE_API UStatWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintCallable)
	void StatUpdate(StatType type, int amount);

	UFUNCTION(BlueprintCallable)
	void PlLevelUpdate(int32 Level);
	UFUNCTION(BlueprintCallable)
	void HPUpdate(int32 HP);
	UFUNCTION(BlueprintCallable)
	void MPUpdate(int32 MP);
	UFUNCTION(BlueprintCallable)
	void STRUpdate(int32 STR);
	UFUNCTION(BlueprintCallable)
	void DEXUpdate(int32 DEX);
	UFUNCTION(BlueprintCallable)
	void INTUpdate(int32 INT);
	UFUNCTION(BlueprintCallable)
	void BonusPointUpdate(int32 BonusPoint);

	void UpdateStatDisplay();
	
	UFUNCTION()
	void HPDownClick();
	UFUNCTION()
	void HPUpClick();
	UFUNCTION()
	void MPDownClick();
	UFUNCTION()
	void MpUpClick();
	UFUNCTION()
	void STRDownClick();
	UFUNCTION()
	void STRUpClick();
	UFUNCTION()
	void DEXDownClick();
	UFUNCTION()
	void DEXUpClick();
	UFUNCTION()
	void INTDownClick();
	UFUNCTION()
	void INTUpClick();

	//te
	UPROPERTY(meta = (BindWidget))
	class UUniformGridPanel* SlotGrid;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<class UButton*> _slotBtns;
	TArray<class UTextBlock*> _slotBtnText;
	
	// 현재 Button, Textblock slotGrid 산하에 있음 
	//button
	UPROPERTY(meta = (BindWidget))
	class UButton* HPDown;
	UPROPERTY(meta = (BindWidget))
	class UButton* HPUp;
	UPROPERTY(meta = (BindWidget))
	class UButton* MPDown;
	UPROPERTY(meta = (BindWidget))
	class UButton* MPUp;
	UPROPERTY(meta = (BindWidget))
	class UButton* STRDown;
	UPROPERTY(meta = (BindWidget))
	class UButton* STRUp;
	UPROPERTY(meta = (BindWidget))
	class UButton* DEXDown;
	UPROPERTY(meta = (BindWidget))
	class UButton* DEXUp;
	UPROPERTY(meta = (BindWidget))
	class UButton* INTDown;
	UPROPERTY(meta = (BindWidget))
	class UButton* INTUp;

	// stat Num
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* HPNum;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* MPNum;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* STRNum;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* DEXNum;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* INTNum;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* BonusNum;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* PlLevel;

	class UTextBlock* PlName;


};
