// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/PlayerBarWidget.h"
#include "Components/ProgressBar.h"

void UPlayerBarWidget::SetPlHPBar(float ratio)
{
	Pl_HPBar->SetPercent(ratio);

}

void UPlayerBarWidget::SetPlMPBar(float ratio)
{
	Pl_MPBar->SetPercent(ratio);
}

void UPlayerBarWidget::SetPlExpBar(float ratio)
{
	Pl_ExpBar->SetPercent(ratio);
}
