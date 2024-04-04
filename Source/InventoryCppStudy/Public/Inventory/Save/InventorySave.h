// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "../../../Public/Inventory/ItemStructs.h"
#include "InventorySave.generated.h"


/**
 * 
 */

struct FItemStruct;

UCLASS()
class INVENTORYCPPSTUDY_API UInventorySave : public USaveGame
{
	GENERATED_BODY()

public:
	UInventorySave();

	UPROPERTY(BlueprintReadWrite, Category = "Inventory")
	FString PlayerCharacterName;

	UPROPERTY(BlueprintReadWrite, Category = "Inventory")
	int32 TotalSlots;

	UPROPERTY(BlueprintReadWrite, Category = "Inventory")
	TArray<FItemStruct> InventoryItems;

	
	
};
