// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Monster.h"
#include "NormalMonster.generated.h"


UCLASS()
class PROTOTYPE_API ANormalMonster : public AMonster
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ANormalMonster();

	virtual FString GetHitSoundName() const override;
	virtual FString GetGuardOff() const override;
	virtual FString GetDeadSoundName() const override;

	void PlayFindEffect();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;
	virtual void Attack_AI() override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Animation", meta = (AllowPrivateAccess = "true"))
	class UMonster_N_AnimInstance* _monster_N_AnimInstance;

	bool first = true;
};
