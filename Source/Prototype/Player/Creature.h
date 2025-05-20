// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "../Component/StatComponent.h"
#include "Creature.generated.h"


DECLARE_MULTICAST_DELEGATE(Delegate_AttackEnded);
UCLASS()
class PROTOTYPE_API ACreature : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACreature();
	Delegate_AttackEnded _attackEndedDelegate;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void PostInitializeComponents() override;
	virtual void Init();
	virtual void Disable();
	virtual void AttackHit();
		
	//VFX
	virtual FString GetHitSoundName() const;
	virtual FString GetSwingSoundName() const;
	virtual FString GetGuardOn() const;
	virtual FString GetGuardOff() const;
	virtual FString GetDeadSoundName() const;
	virtual FString GetSkillSound01() const;
	virtual FString GetSkillSound02() const;
	virtual FString GetSkillSound03() const;
	virtual FString GetSkillSound03Shout() const;
	virtual FString GetSkillSound04Start() const;
	virtual FString GetSkillSound04Durring() const;

	virtual FString GetBossMonsterAttack() const;
	virtual FString GetSkillParticleEffect02() const;
	virtual FString GetPlayerAttackHitEffect() const;
	virtual FString GetEpicAttackFarSound() const;
	virtual FString GetEpicAttackMagicDotSound() const;
	virtual FString GetPlayerSkillEffect04_Start() const;
	virtual FString GetPlayerSkillEffect04_Durring() const;
	virtual FString GetUIBaseSound() const;
	virtual FString GetEpicSkeletonEffect() const;
	virtual FString GetEpicSpawnSound() const;
	virtual FString GetLevelUpSound() const;

	bool GetIsAttacking() {return _isAttacking;}

	UFUNCTION()
	virtual  void OnAttackEnded(class UAnimMontage* Montage, bool bInterrupted);

	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser);

	float GetVertical() {return _vertical;}
	float GetHorizontal() {return _horizontal;}
	int32 GetCurHp() { return _StatCom->GetCurHp(); }

	// cheol
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat, meta = (AllowPrivateAccess = "true"))
	UStatComponent* _StatCom;

	FTimerHandle TimerHandle_Destroy;

	UFUNCTION()
	void DelayedDestroy();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	bool _isAttacking = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	int32 _curAttackIndex = 1;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	float _vertical = 0.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	float _horizontal = 0.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = AttackHit, meta = (AllowPrivateAccess = "true"))
	FVector _hitPoint;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stat, meta = (AllowPrivateAccess = "true"))
	class UWidgetComponent* _hpWidget;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Guard, meta = (AllowPrivateAccess = "true"))
	bool bIsGuarding;

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = UI, meta = (AllowPrivateAccess = "true"))
	class UWidgetComponent* _WidgetCom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = UI, meta = (AllowPrivateAccess = "true"))
	class UUserWidget* _Widget;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = UI, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UUserWidget> WidgetClass;

	
	bool _isTransformed;

	UFUNCTION(BlueprintCallable, Category = "UI")
	UUserWidget* GetWidget() const { return _Widget; }

};
