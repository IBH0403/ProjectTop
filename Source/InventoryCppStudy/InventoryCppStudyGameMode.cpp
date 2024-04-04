// Copyright Epic Games, Inc. All Rights Reserved.

#include "InventoryCppStudyGameMode.h"
#include "InventoryCppStudyCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "InventoryCppStudy/Public/Inventory/Save/InventoryState.h"

AInventoryCppStudyGameMode::AInventoryCppStudyGameMode()
{
	// set default pawn class to our Blueprinted character
	//static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Inventory/BluePrint/Characters/BP_InventoryCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

void AInventoryCppStudyGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	/*ASPlayerState* PlayerState = NewPlayer->GetPlayerState<ASPlayerState>();
	if (true == ::IsValid(PlayerState))
	{
		PlayerState->InitPlayerState();
	}*/
	UE_LOG(LogTemp, Error, TEXT("PostLogin Start"));
	AInventoryState* InventoryState = NewPlayer->GetPlayerState<AInventoryState>();
	if (true == ::IsValid(InventoryState))
	{
		InventoryState->InitInventoryState();
	}
	
}
