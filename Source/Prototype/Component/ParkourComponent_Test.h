// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ParkourComponent_Test.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROTOTYPE_API UParkourComponent_Test : public UActorComponent
{
	GENERATED_BODY()
public:
	// Sets default values for this component's properties
	UParkourComponent_Test();

	// 등반 관련 플래그
	bool bIsClimbing;

protected:
	virtual void BeginPlay() override;

public:	
	// 벽에 매달리기
	void StartClimbing(FVector WallNormal);

	// 벽 등반 중 캐릭터 이동
	void ClimbMove(float AxisValueForward, float AxisValueRight);

	// 등반 종료
	void StopClimbing();

	// 캐릭터 참조
	UPROPERTY()
	class AMyPlayer* Character;

	// 벽의 방향 저장
	FVector CurrentWallNormal;

	// 등반 속도
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Climbing")
	float ClimbSpeed;
};