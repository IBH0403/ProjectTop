// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Item.h"
#include "WBP_ItemInfo.generated.h"

// This class does not need t
UCLASS()
class GACHA_API UWBP_ItemInfo : public UUserWidget
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	FItem ItemInfo;
};
