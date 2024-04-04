// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory/Actors/Food.h"
//#include "InventoryCppStudy/InventoryCppStudyCharacter.h"
#include "../InventoryCppStudyCharacter.h"
#include "../../ProjectTop/ProjectTopCharacter.h"

AFood::AFood()
{
	HungerValue = 10.f;
	ItemStruct.ItemClass = StaticClass();
}

void AFood::ClickItem(AInventoryCppStudyCharacter* Character)
{
	if (Character)
	{
		Character->RemoveHunger(HungerValue);
	}
}

void AFood::ClickItem(AProjectTopCharacter* Character)
{
	if (Character)
	{
		Character->RemoveHunger(HungerValue);
	}
}