// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Monster/Monster.h"
#include "Boss2Monster.generated.h"

/**
 * 
 */
UCLASS()
class PROTOTYPE_API ABoss2Monster : public AMonster
{
	GENERATED_BODY()
public:
	ABoss2Monster();
	void Skill_AI(FVector location);
	void Teleport(FVector location);

	virtual FString GetBoss2AttackEffect() const;
	virtual FString GetBoss2TeleportEffect() const;
	virtual FString GetBoss2TeleportSound() const;

	bool GetIsfire(){return Isfire;}

private:
	virtual void BeginPlay() override;
	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser);
	virtual void PostInitializeComponents() override;
	virtual void Attack_AI() override;
	virtual void AttackHit() override;
	

	UFUNCTION()
	void FireballAttack(FVector Location);


	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Animation", meta = (AllowPrivateAccess = "true"))
	class UMonster_Boss2_AnimInstance* _bossMonster02_AnimInstance;

	FVector UpdatedLocation();
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Fireball", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class ABossFireball> _fireball;	

	UPROPERTY()
    class USunderPool* SunderPool;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class ABossSunder> _sunder;

	bool Isfire;
};
