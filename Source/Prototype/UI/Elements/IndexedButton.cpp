// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Elements/IndexedButton.h"
#include "Base/MyGameInstance.h"
#include "Base/Managers/UIManager.h"
#include "Styling/SlateTypes.h"
#include "Components/Image.h"

void UIndexedButton::ButtonUpdate()
{
	FSlateBrush imageBrush;

	if (_item)
		SetImage(_item->GetTexture());
	else
		SetImage(T_DEFAULT);

	if (_image != nullptr)
		imageBrush.SetResourceObject(_image);
	else
		imageBrush.SetResourceObject(T_DEFAULT);

	imageBrush.ImageSize = FVector2D(200.0f, 200.0f);

	FButtonStyle btnStyle;
	btnStyle.SetNormal(imageBrush);
	btnStyle.SetHovered(imageBrush);
	btnStyle.SetPressed(imageBrush);
	
	this->SetStyle(btnStyle);
}
