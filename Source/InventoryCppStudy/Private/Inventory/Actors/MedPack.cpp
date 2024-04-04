// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory/Actors/MedPack.h"
#include "../InventoryCppStudyCharacter.h"
#include "../../ProjectTop/ProjectTopCharacter.h"

AMedPack::AMedPack()
{
	HealthValue = 10.f;
	ItemStruct.ItemClass = StaticClass();
}

void AMedPack::ClickItem(AInventoryCppStudyCharacter* Character)
{
	if (Character)
	{
		Character->AddHp(HealthValue);
	}
}

void AMedPack::ClickItem(AProjectTopCharacter* Character)
{
	if (Character)
	{
		Character->AddHp(HealthValue);
	}
}