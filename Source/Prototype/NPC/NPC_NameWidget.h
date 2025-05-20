// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "NPC_NameWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROTOTYPE_API UNPC_NameWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void SetNPC_Name(FString name);

private:
	UPROPERTY(meta = (BindWidget))
	class  UTextBlock* NPC_Name;
};
