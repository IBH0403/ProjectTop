// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/UserDefinedStruct.h"
#include "ItemData.generated.h"

/**
 * 
 */
UCLASS()
class INVENTORYCPPSTUDY_API UItemData : public UUserDefinedStruct
{
	GENERATED_BODY()
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class AItemActor> ItemClass;  //ItemID

	UPROPERTY(EditDefaultsOnly)
	class UTexture2D* ItemImage;

	UPROPERTY(EditDefaultsOnly)
	float ItemCost; //Attack

	//Item Name   
	//Item Grade  1~4
};

