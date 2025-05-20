// Fill out your copyright notice in the Description page of Project Settings.


#include "UpperArmor.h"


AUpperArmor::AUpperArmor()
{
    _equipItemType = EItemType::UpperArmor;
    AttachSocketName = FName(TEXT("spine_03Socket"));
}

void AUpperArmor::BeginPlay()
{
    Super::BeginPlay();

    SetItemWithCode(3);
}
