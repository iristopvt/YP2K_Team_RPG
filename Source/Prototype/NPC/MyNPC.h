// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyNPC.generated.h"

class AMyPlayer;

UCLASS()
class PROTOTYPE_API AMyNPC : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyNPC();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void PostInitializeComponents() override;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	AMyPlayer* GetConvTarget() { return _target; }

	int32 GetShopCode() { return _shopCode; }
	
	UFUNCTION()
	void Interect();
private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shop", meta = (AllowPrivateAccess = "true"))
	FString _NPCName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shop", meta = (AllowPrivateAccess = "true"))
	int32 _shopCode;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player", meta = (AllowPrivateAccess = "true"))
	AMyPlayer* _target;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Collision", meta = (AllowPrivateAccess = "true"))
	class USphereComponent* _trigger;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh", meta = (AllowPrivateAccess = "true"))
	class USkeletalMeshComponent* _skeletalMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Overlap", meta = (AllowPrivateAccess = "true"))
	bool _isOverlapped;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shop", meta = (AllowPrivateAccess = "true"))
	class UShopComponent* _shopComp;

	class UNPC_NameWidget* _nameWidget;
};
