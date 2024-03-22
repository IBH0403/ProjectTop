// Copyright Epic Games, Inc. All Rights Reserved.
// gachaGameMode.h
#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "GameFramework/GameModeBase.h"
#include "gachaGameMode.generated.h"

UCLASS(minimalapi)
class AgachaGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AgachaGameMode();
	UFUNCTION(BlueprintCallable, Category = "Random")
	void DrawResult();
	UFUNCTION(BlueprintCallable, Category = "Random")
	void PlaySequence(const FString& SequencePath);
	UFUNCTION(BlueprintCallable, Category = "Random")
	FItem DrawItemTable(const UDataTable* ItemDataTable);
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "DataTables")
	UDataTable* DrawResultTable;


protected:
	int32 GetRandomResult() const;
};



