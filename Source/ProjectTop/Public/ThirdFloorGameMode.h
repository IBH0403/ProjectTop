// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ThirdFloorGameMode.generated.h"

/**
 *
 */
UCLASS()
class PROJECTTOP_API AThirdFloorGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	void ActorDied(AActor* DeadActor);

protected:
	virtual void BeginPlay() override;


private:
	class AMonsterForThirdFloor* Monster;
};
