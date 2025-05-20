// Fill out your copyright notice in the Description page of Project Settings.


#include "Sword.h"


ASword::ASword()
{
    _equipItemType = EItemType::Sword;
    AttachSocketName = FName(TEXT("hand_rSocket"));
}

void ASword::BeginPlay()
{
    SetItemWithCode(5);
}
