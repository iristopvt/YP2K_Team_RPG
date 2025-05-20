// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/EpicMonster2.h"

AEpicMonster2::AEpicMonster2()
{
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> EP(TEXT("/Script/Engine.SkeletalMesh'/Game/Monster/Mesh/SK_Monster.SK_Monster'"));
	
	if (EP.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(EP.Object);
	}
}

void AEpicMonster2::BeginPlay()
{
	Super::BeginPlay();
}

void AEpicMonster2::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}
