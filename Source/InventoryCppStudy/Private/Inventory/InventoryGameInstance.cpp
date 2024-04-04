// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory/InventoryGameInstance.h"

void UInventoryGameInstance::Init()
{
    Super::Init();

    if (false == ::IsValid(InventoryStatDataTable) || InventoryStatDataTable->GetRowMap().Num() <= 0)
    {
        UE_LOG(LogTemp, Error, TEXT("Not enuough data in CharacterStatDataTable."));
    }
    else
    {
        for (int32 i = 1; i <= InventoryStatDataTable->GetRowMap().Num(); ++i)
        {
            check(nullptr != GetCharacterStatDataTableRow(i));
        }
    }
}

void UInventoryGameInstance::Shutdown()
{
    Super::Shutdown();
}

FInventoryTableRow* UInventoryGameInstance::GetCharacterStatDataTableRow(int32 InLevel)
{
    if (true == ::IsValid(InventoryStatDataTable))
    {
        return InventoryStatDataTable->FindRow<FInventoryTableRow>(*FString::FromInt(InLevel), TEXT(""));
    }

    return nullptr;
}