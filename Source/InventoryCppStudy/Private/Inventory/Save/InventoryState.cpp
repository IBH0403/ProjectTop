// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory/Save/InventoryState.h"
#include "InventoryCppStudy/Public/Inventory/InventoryGameInstance.h"
#include "InventoryCppStudy/Public/Inventory/Save/InventorySave.h"
#include "Kismet/GameplayStatics.h"

FString AInventoryState::SaveSlotName(TEXT("Inventory"));

AInventoryState::AInventoryState()
{
}

void AInventoryState::InitInventoryState()
{
	GameInstance = Cast<UInventoryGameInstance>(GetWorld()->GetGameInstance());
    if (true == ::IsValid(GameInstance))
    {
        if (nullptr != GameInstance->GetCharacterStatDataTable() || nullptr != GameInstance->GetCharacterStatDataTableRow(1))
        {
            /*MaxLevel = GameInstance->GetCharacterStatDataTable()->GetRowMap().Num();
            CurrentLevel = 1;
            CurrentEXP = 0;
            MaxEXP = SGI->GetCharacterStatDataTableRow(1)->MaxEXP;*/
        }
    }


    UInventorySave* InventorySave = Cast<UInventorySave>(UGameplayStatics::LoadGameFromSlot(SaveSlotName, 0));
    if (false == ::IsValid(InventorySave))
    {
        InventorySave = GetMutableDefault<UInventorySave>();


        for (int i = 0; i < InventorySave->TotalSlots; i++)
        {
            InventorySave->InventoryItems[i].ItemClass = TSubclassOf<AItemActor>();
            InventorySave->InventoryItems[i].ItemCost = -1.f;
            InventorySave->InventoryItems[i].ItemImage = nullptr;
        }
    }
    

    SetPlayerName(InventorySave->PlayerCharacterName);
    SetTotalSlots(InventorySave->TotalSlots);
    SetInventoryItems(InventorySave->InventoryItems);


    SaveInventoryState();
}


void AInventoryState::SaveInventoryState()
{

    UInventorySave* NewSave = NewObject<UInventorySave>();
    NewSave->PlayerCharacterName = GetPlayerName();
    NewSave->TotalSlots = GetTotalSlots();
    NewSave->InventoryItems = GetInventoryItems();

    if (true == UGameplayStatics::SaveGameToSlot(NewSave, SaveSlotName, 0))
    {
        UE_LOG(LogTemp, Error, TEXT("InventoryState.cpp Saved"));
    }
}

void AInventoryState::SetPlyaerCharacterName(FString Name)
{
}

void AInventoryState::SetTotalSlots(int32 slots)
{
}

void AInventoryState::SetInventoryItems(TArray<FItemStruct> Items)
{
    InventoryItems = Items;

    SaveInventoryState();
}
