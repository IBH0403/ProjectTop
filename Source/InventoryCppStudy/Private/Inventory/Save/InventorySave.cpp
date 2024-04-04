// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory/Save/InventorySave.h"
#include "Inventory/Actors/Food.h"

UInventorySave::UInventorySave()
{
	PlayerCharacterName = TEXT("InitialCharacter");

	TotalSlots = 28;

	FItemStruct DefaultItemData;
	DefaultItemData.ItemClass = TSubclassOf<AItemActor>();
	DefaultItemData.ItemCost = -1.f;
	DefaultItemData.ItemImage = nullptr;

	for (int i = 0; i < TotalSlots; i++)
	{
		InventoryItems.Add(DefaultItemData);
	}
	
}
