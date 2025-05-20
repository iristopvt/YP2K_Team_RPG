// Fill out your copyright notice in the Description page of Project Settings.


#include "Helmet.h"


AHelmet::AHelmet()
{
    _equipItemType = EItemType::Helmet;
     AttachSocketName = FName(TEXT("headSocket"));
}

void AHelmet::BeginPlay()
{
    Super::BeginPlay();

    SetItemWithCode(1);
}
