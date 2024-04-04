// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "InventoryCppStudyGameMode.generated.h"

UCLASS(minimalapi)
class AInventoryCppStudyGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AInventoryCppStudyGameMode();

	virtual void PostLogin(APlayerController* NewPlayer) override;
};



