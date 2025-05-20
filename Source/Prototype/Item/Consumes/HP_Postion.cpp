// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/Consumes/HP_Postion.h"
#include "Base/MyGameInstance.h"

AHP_Postion::AHP_Postion()
{
	
}

void AHP_Postion::BeginPlay()
{
	Super::BeginPlay();

	SetItemWithCode(2);
}
