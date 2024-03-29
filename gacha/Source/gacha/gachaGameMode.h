// Copyright Epic Games, Inc. All Rights Reserved.
// gachaGameMode.h
#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Public/Item.h"
#include "GameFramework/GameModeBase.h"
#include "Runtime/LevelSequence/Public/LevelSequenceActor.h"
#include "Runtime/LevelSequence/Public/LevelSequencePlayer.h"
#include "Runtime/LevelSequence/Public/LevelSequence.h"
#include "Blueprint/UserWidget.h"
#include "gachaGameMode.generated.h"

UCLASS(minimalapi)
class AgachaGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
    AgachaGameMode();

    UFUNCTION(BlueprintCallable, Category = "Random")
    void PlaySequence(const FString& SequencePath);

    UFUNCTION(BlueprintCallable, Category = "Random")
    FItem DrawItemTable(const UDataTable* ItemDataTable);

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Widget")
    TSubclassOf<UUserWidget> ItemInfoWidgetClass;

    UPROPERTY(BlueprintReadWrite)
    FItem CurrentItemInfo;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "DataTables")
    UDataTable* DrawResultTable;

    UPROPERTY()
    ULevelSequencePlayer* LevelSequencePlayer;

    UFUNCTION(BlueprintCallable, Category = "Random")
    void StopSequence();

    UFUNCTION(BlueprintImplementableEvent, Category = "Widget")
    void CreateItemInfoWidget(const FItem& FItem);

    /*UFUNCTION()
    void OnSequenceFinished();*/
};