// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "InteractableInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UInteractableInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class AInventoryCppStudyCharacter;
class AInventoryCharacter;
class AProjectTopCharacter;

class INVENTORYCPPSTUDY_API IInteractableInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	// virtual ~~ = 0 means it should be implemented if some class inherits this interface.
	virtual void Interact(AInventoryCppStudyCharacter* Character) = 0;
	//virtual void Interact() {}
	virtual void ClickItem(AInventoryCppStudyCharacter* Character) {}

	virtual void Interact(AInventoryCharacter* Character) = 0;

	virtual void ClickItem(AInventoryCharacter* Character) {}

	virtual void Interact(AProjectTopCharacter* Character) = 0;

	virtual void ClickItem(AProjectTopCharacter* Character) {}
};
