// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/IconTestWidget.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/Image.h"
void UIconTestWidget::NativeConstruct()
{
}

void UIconTestWidget::UpdateLocation(FVector2D& InPosition)
{
	FVector2D Normalize2D = InPosition.GetSafeNormal();

	float Length = InPosition.Size();

	float clamp = FMath::Clamp(Length, 0, 1500);

	FVector2D Final = Normalize2D * clamp;

	float FinalX = Final.X * -0.12 + 196;
	float FinalY = Final.Y * 0.12 + -196;

	//InPosition.SloatasCanvasClot
	UPROPERTY(meta = (BindWidget))

		if (UCanvasPanelSlot* CanvasSlot = Cast<UCanvasPanelSlot>(conImage->Slot))
		{

			CanvasSlot->SetPosition(FVector2D(FinalX, FinalY));
		}
	//conImage 
}