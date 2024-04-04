// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "../ItemStructs.h"
#include "InventoryState.generated.h"

/**
 * 
 */
UCLASS()
class INVENTORYCPPSTUDY_API AInventoryState : public APlayerState
{
	GENERATED_BODY()


public:
	AInventoryState();

	void InitInventoryState();

	static FString SaveSlotName;

	void SaveInventoryState();

	FString GetPlayerCharacterName() { return PlayerCharacterName; }

	int32 GetTotalSlots() const { return TotalSlots; }

	TArray<FItemStruct> GetInventoryItems() const { return InventoryItems; }

	void SetPlyaerCharacterName(FString Name);

	void SetTotalSlots(int32 slots);

	void SetInventoryItems(TArray<FItemStruct> Items);

private:
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "InventoryState", Meta = (AllowPrivateAccess = true))
	TObjectPtr<class UInventoryGameInstance> GameInstance;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "InventoryState", Meta = (AllowPrivateAccess = true))
    int32 SlotIndex = 0;

    UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "InventoryState", Meta = (AllowPrivateAccess = true))
    FItemStruct ItemData;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "InventoryState", Meta = (AllowPrivateAccess = true))
	FString PlayerCharacterName;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "InventoryState", Meta = (AllowPrivateAccess = true))
	int32 TotalSlots;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "InventoryState", Meta = (AllowPrivateAccess = true))
	TArray<FItemStruct> InventoryItems;



//public:
//    AInventoryState();
//
//    void InitPlayerState();
//
//    int32 GetMaxLevel() const { return MaxLevel; }
//
//    int32 GetCurrentLevel() const { return CurrentLevel; }
//
//    float GetMaxEXP() const { return MaxEXP; }
//
//    float GetCurrentEXP() const { return CurrentEXP; }
//
//    void SetCurrentLevel(int32 InCurrentLevel);
//
//    void SetCurrentEXP(float InCurrentEXP);
//
//    void SavePlayerState();
//
//
//public:
//    FOnCurrentLevelChangedDelegate OnCurrentLevelChangedDelegate;
//
//    FOnCurrentEXPChangedDelegate OnCurrentEXPChangedDelegate;
//
//    static FString SaveSlotName;
//
//private:
//    UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "InventoryState", Meta = (AllowPrivateAccess = true))
//    TObjectPtr<class USGameInstance> SGI;
//
//    UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "InventoryState", Meta = (AllowPrivateAccess = true))
//    int32 MaxLevel = 5;
//
//    UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "InventoryState", Meta = (AllowPrivateAccess = true))
//    int32 CurrentLevel = 1;
//
//    UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "InventoryState", Meta = (AllowPrivateAccess = true))
//    float MaxEXP = 150;
//
//    UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "InventoryState", Meta = (AllowPrivateAccess = true))
//    float CurrentEXP = 0;
	
};
