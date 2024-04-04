// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
//
//#include "CoreMinimal.h"
//
///**
// * 
// */
//class INVENTORYCPPSTUDY_API ItemStructs
//{
//public:
//	ItemStructs();
//	~ItemStructs();
//};

#include "ItemStructs.generated.h"

USTRUCT(BlueprintType)
struct FItemStruct
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSubclassOf<class AItemActor> ItemClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	class UTexture2D* ItemImage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float ItemCost;
};