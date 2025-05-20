// Fill out your copyright notice in the Description page of Project Settings.


#include "Shield.h"


AShield::AShield()
{
    _equipItemType = EItemType::Shield;
    AttachSocketName = FName(TEXT("lowerarm_twist_02_lSocket"));
}

void AShield::BeginPlay()
{
    SetItemWithCode(6);
}


