// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Managers/EffectManager.h"
#include "Managers/SoundManager.h"
#include "Component/StatComponent.h"
#include "Component/InventoryComponent.h"
#include "../Item/BaseItem.h"
#include "Item/Equip/EquipItem.h"
#include "../Component/ShopComponent.h"
#include "MyGameInstance.generated.h"

#define GAMEINSTANCE Cast<UMyGameInstance>(GetWorld()->GetGameInstance())
#define UIManager Cast<UMyGameInstance>(GetWorld()->GetGameInstance())->GetUIManager()
#define T_DEFAULT Cast<UMyGameInstance>(GetWorld()->GetGameInstance())->GetUIManager()->GetDefaultTexture()
#define SoundManager Cast<UMyGameInstance>(GetGameInstance())->GetSoundManager()
#define EffectManager Cast<UMyGameInstance>(GetGameInstance())->GetEffectManager()

UCLASS()
class PROTOTYPE_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UMyGameInstance();
	void SavePlayerStats(class UStatComponent* StatComponent);
	void LoadPlayerStats(class UStatComponent* StatComponent);

	void SaveInventory(class UInventoryComponent* InventoryComponent);
	void LoadInventory(class UInventoryComponent* InventoryComponent);

	void SavePlayerSkeletal(class AMyPlayer* player);
	void LoadPlayerSkeletal(class AMyPlayer* player);

    UPROPERTY()
    TArray<FItemData> SavedInventoryData;

	UPROPERTY()
	TMap<FString,FItemData> SavedEquipData;
    

	bool GetFirst(){return _firstIn;}
	void SetFirst(bool first){_firstIn = first;}

	bool GetStage1Clear(){return _stage1Clear;}
	void SetStage1Clear(bool clear){_stage1Clear = clear;}

	bool GetStage2Clear(){return _stage2Clear;}
	void SetStage2Clear(bool clear){_stage2Clear = clear;}

	TArray<ABaseItem*> GetInvenItemList();

public:
	virtual void Init() override;

	UFUNCTION()
	void InitializeManagers();
	
	class AUIManager* GetUIManager() { return _UIManager; }

	FMyStatData* GetStatDataByLevel(int level);
	FMyStatData* GetMonsterDataByLevel(int level);
	FMyStatData* GetEpicDataByLevel(int level);
	FMyStatData* GetBossDataByLevel(int level);
	FMyStatData* GetDragonDataByLevel(int level);

	FItemData* GetConsumeItemData(int code);
	FItemData* GetEquipItemData(int code);

	TArray<FSellings*> GetSellingData(int32 shop);

	ABaseItem* SellDataToItemData(FSellings* data);

	ASoundManager* GetSoundManager() { return _soundManager; }
	AEffectManager* GetEffectManager() { return _effectManager; }

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Audio")
	float MasterVolume = 1.0f;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class AUIManager* _UIManager;

	UPROPERTY()
	UDataTable* _statTable;

	UPROPERTY()
	UDataTable* _EpicstatTable;

	UPROPERTY()
	UDataTable* _BossstatTable;
	
	UPROPERTY()
	UDataTable* _MonsterstatTable;

	UPROPERTY()
	UDataTable* _ConsItemTable;
	UPROPERTY()
	UDataTable* _EquipItemTable;

	UPROPERTY()
	UDataTable* _ShopList;

	UPROPERTY()
	TArray<UDataTable*> _ShopLists;

	UPROPERTY()
	UDataTable* _DragonStatTable;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	ASoundManager* _soundManager;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	AEffectManager* _effectManager;

	UPROPERTY()
	int32 _savedLevel;

	UPROPERTY()
	int32 _savedMaxHp;
	UPROPERTY()
	int32 _savedCurHp;
	UPROPERTY()
	int32 _savedOgHp;
	UPROPERTY()
	int32 _savedModHp;

	UPROPERTY()
	int32 _savedMaxMp;
	UPROPERTY()
	int32 _savedCurMp;
	UPROPERTY()
	int32 _savedOgMp;
	UPROPERTY()
	int32 _savedModMp;


	UPROPERTY()
	int32 _savedStr;
	UPROPERTY()
	int32 _savedOgStr;
	UPROPERTY()
	int32 _savedModStr;

	UPROPERTY()
	int32 _savedDex;
	UPROPERTY()
	int32 _savedOgDex;
	UPROPERTY()
	int32 _savedModDex;

	UPROPERTY()
	int32 _savedInt;
	UPROPERTY()
	int32 _savedOgInt;
	UPROPERTY()
	int32 _savedModInt;

	UPROPERTY()
	float _savedAttackRadius;

	UPROPERTY()
	float _savedAttackRange;

	UPROPERTY()
	int32 _savedExp;
	UPROPERTY()
	int32 _savedNextExp;
	UPROPERTY()
	int32 _savedBonus;

	UPROPERTY()
	int32 _savedMoney;

	UPROPERTY()
	class USkeletalMesh* _savedBodyMesh;
	UPROPERTY()
	class USkeletalMesh* _savedLowerBodyMesh;
	UPROPERTY()
	class USkeletalMesh* _savedShoulderBodyMesh;
	UPROPERTY()
	class USkeletalMesh*_savedSwordBodyMesh;
	UPROPERTY()
	class USkeletalMesh* _savedShieldBodyMesh;
	
	UPROPERTY()
	bool _firstIn = true;

	UPROPERTY()
	bool _stage1Clear = false;

	UPROPERTY()
	bool _stage2Clear = false;



};
