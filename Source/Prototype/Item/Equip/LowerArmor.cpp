// Fill out your copyright notice in the Description page of Project Settings.


#include "LowerArmor.h"


ALowerArmor::ALowerArmor()
{
    _equipItemType = EItemType::LowerArmor;
    AttachSocketName = FName(TEXT("pelvisSocket"));
}

void ALowerArmor::BeginPlay()
{
    Super::BeginPlay();

    SetItemWithCode(4);
}
