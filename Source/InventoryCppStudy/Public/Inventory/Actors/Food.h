// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Inventory/Actors/ItemActor.h"
#include "Food.generated.h"

/**
 * 
 */
class AInventoryCppStudyCharacter;
class AProjectTopCharacter;

UCLASS()
class INVENTORYCPPSTUDY_API AFood : public AItemActor
{
	GENERATED_BODY()

public:
	AFood();

protected:
	UPROPERTY(EditAnywhere, Category = "Inventory")
	float HungerValue;


public:
	virtual void ClickItem(AInventoryCppStudyCharacter* Character) override;
	
	virtual void ClickItem(AProjectTopCharacter* Character) override;
};
