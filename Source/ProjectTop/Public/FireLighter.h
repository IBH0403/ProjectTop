// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "FireLighter.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class PROJECTTOP_API UFireLighter : public USceneComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UFireLighter();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly, Category = "FireLighting")
	bool HasHit = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FireLighting")
	int32 HitAttempts = 0;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = "FireLighting")
	void Light();

	UFUNCTION(BlueprintCallable, Category = "FireLighting")
	void Release();

	// UFUNCTION(BlueprintImplementableEvnet, Category = "FireLighting")
	// void CallBlueprint();

private:
	UPROPERTY(EditAnywhere)
	float MaxFireLightDistance = 70;

	UPROPERTY(EditAnywhere)
	float FireLightRadius = 130;

	UPROPERTY(EditAnywhere)
	float HoldDistance = 200;

	FTimerHandle FireLighterTimerHandle;

};
