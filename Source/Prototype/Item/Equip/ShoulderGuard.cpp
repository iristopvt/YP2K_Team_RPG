// Fill out your copyright notice in the Description page of Project Settings.


#include "ShoulderGuard.h"


AShoulderGuard::AShoulderGuard()
{
    _equipItemType = EItemType::ShoulderArmor;
    AttachSocketName = FName(TEXT("chest_playeSocket"));
}

void AShoulderGuard::BeginPlay()
{
    Super::BeginPlay();

    SetItemWithCode(2);
}
