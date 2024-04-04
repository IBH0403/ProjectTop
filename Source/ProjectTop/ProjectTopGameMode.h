// ProjectTopGameMode.h

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "GameFramework/GameModeBase.h"
#include "Runtime/LevelSequence/Public/LevelSequenceActor.h"
#include "Runtime/LevelSequence/Public/LevelSequencePlayer.h"
#include "Runtime/LevelSequence/Public/LevelSequence.h"
#include "ProjectTopGameMode.generated.h"

UCLASS(minimalapi)
class AProjectTopGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AProjectTopGameMode();

	UFUNCTION(BlueprintCallable, Category = "Random")
	void PlaySequence(const FString& SequencePath);

	UFUNCTION(BlueprintCallable, Category = "Random")
	FItem DrawItemTable(const UDataTable* ItemDataTable);

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "DataTables")
	UDataTable* DrawResultTable;

	UPROPERTY()
	ULevelSequencePlayer* LevelSequencePlayer;

	UFUNCTION(BlueprintCallable, Category = "Random")
	void StopSequence();

	UFUNCTION(BlueprintCallable)
	void OnSequenceFinished();



	//Inventory
	virtual void PostLogin(APlayerController* NewPlayer) override;
};
