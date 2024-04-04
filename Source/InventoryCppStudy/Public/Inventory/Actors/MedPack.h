// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Inventory/Actors/ItemActor.h"
#include "MedPack.generated.h"

/**
 * 
 */

class AInventoryCppStudyCharacter;
class AProjectTopCharacter;

UCLASS()
class INVENTORYCPPSTUDY_API AMedPack : public AItemActor
{
	GENERATED_BODY()

public:
	AMedPack();

protected:
	UPROPERTY(EditAnywhere, Category = "Inventory")
	float HealthValue;

public:
	virtual void ClickItem(AInventoryCppStudyCharacter* Character) override;
	
	virtual void ClickItem(AProjectTopCharacter* Character) override;
};
