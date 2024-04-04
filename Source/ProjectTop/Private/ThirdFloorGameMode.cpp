// Fill out your copyright notice in the Description page of Project Settings.


#include "ThirdFloorGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "MonsterForThirdFloor.h"

void AThirdFloorGameMode::ActorDied(AActor* DeadActor)
{
	if (AMonsterForThirdFloor* DestroyedMonster = Cast<AMonsterForThirdFloor>(DeadActor))
	{
		DestroyedMonster->HandleDestruction();
	}
	// else Game Over
}

void AThirdFloorGameMode::BeginPlay()
{
	Super::BeginPlay();

	Monster = Cast<AMonsterForThirdFloor>(UGameplayStatics::GetPlayerCharacter(this, 0));
}