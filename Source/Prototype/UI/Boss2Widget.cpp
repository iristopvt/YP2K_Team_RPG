// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Boss2Widget.h"
#include "Components/ProgressBar.h"


void UBoss2Widget::UpdateBossHPBar(float Ratio)
{
     BossHPBar->SetPercent(Ratio);
}
