// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Engine/DataTable.h"
#include "../../../InventoryCppStudy/Public/Inventory/ItemStructs.h"
#include "InventoryGameInstance.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct FInventoryTableRow : public FTableRowBase
{
    GENERATED_BODY()

public:
    FInventoryTableRow()
    {
    }

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 SlotIndex;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FItemStruct ItemData;

};


UCLASS()
class INVENTORYCPPSTUDY_API UInventoryGameInstance : public UGameInstance
{
	GENERATED_BODY()


public:
    virtual void Init() override;

    virtual void Shutdown() override;

    const UDataTable* GetCharacterStatDataTable() { return InventoryStatDataTable; }

    FInventoryTableRow* GetCharacterStatDataTableRow(int32 InLevel);


private:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "InventoryState", Meta = (AllowPrivateAccess))
    class UDataTable* InventoryStatDataTable;
	
};
