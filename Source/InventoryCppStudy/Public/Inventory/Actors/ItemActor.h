// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../InteractableInterface.h"
#include "../ItemStructs.h"
//#include "../ItemData.h"
#include "ItemActor.generated.h"


class AInventoryCppStudyCharacter;
class AInventoryCharacter;
class AProjectTopCharacter;

UCLASS()
class INVENTORYCPPSTUDY_API AItemActor : public AActor, public IInteractableInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItemActor();

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Inventory")
	UStaticMeshComponent* ItemMesh;

	UPROPERTY(EditDefaultsOnly, Category = "Inventory")
	FItemStruct ItemStruct;


	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame

	FItemStruct GetItemStruct() const { return ItemStruct; }

	/*virtual void Tick(float DeltaTime) override;*/
	virtual void Interact(AInventoryCppStudyCharacter* Character) override;

	virtual void ClickItem(AInventoryCppStudyCharacter* Character) override;

	virtual void Interact(AInventoryCharacter* Character) override;

	virtual void ClickItem(AInventoryCharacter* Character) override;

	virtual void Interact(AProjectTopCharacter* Character) override;

	virtual void ClickItem(AProjectTopCharacter* Character) override;

	

};
