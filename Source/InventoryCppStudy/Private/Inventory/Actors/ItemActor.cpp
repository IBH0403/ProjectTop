// Fill out your copyright notice in the Description page of Project Settings.

#include "Inventory/Actors/ItemActor.h"
#include "Components/StaticMeshComponent.h"
#include "../InventoryCppStudyCharacter.h"
#include "../Public/Inventory/Characters/InventoryCharacter.h"
#include "../../ProjectTop/ProjectTopCharacter.h"

// Sets default values
AItemActor::AItemActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	RootComponent = ItemMesh;

	ItemStruct.ItemClass = StaticClass();

	bReplicates = true;


}

// Called when the game starts or when spawned
void AItemActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void AItemActor::Interact(class AInventoryCppStudyCharacter* Character)
{
	// Only Destroying on Client isn't good
	// 
	//if (Character)
	//{
	//	Character->AddItemToInventoryWidget(ItemStruct);
	//}
	//Destroy();
	UE_LOG(LogTemp, Error, TEXT("ItemActor.cpp Interact Start"));

	if (HasAuthority() && Character)
	{
		/*Character->AddItemToInventoryWidget(ItemStruct);*/
		Character->AddInventoryItem(ItemStruct);
		UE_LOG(LogTemp, Error, TEXT("ItemActor.cpp Interact Inside if branch"));
		Destroy();
	}
}

void AItemActor::ClickItem(AInventoryCppStudyCharacter* Character)
{
	UE_LOG(LogTemp, Warning, TEXT("Clicked Item : %s"), *this->GetName());
	UE_LOG(LogTemp, Warning, TEXT("Used from : %s"), *Character->GetName());
}


void AItemActor::Interact(class AInventoryCharacter* Character)
{
	if (Character)
	{
		Character->AddItemToInventoryWidget(ItemStruct);
	}
	Destroy();
}

void AItemActor::ClickItem(AInventoryCharacter* Character)
{
	UE_LOG(LogTemp, Warning, TEXT("Clicked Item : %s"), *this->GetName());
	UE_LOG(LogTemp, Warning, TEXT("Used from : %s"), *Character->GetName());
}

// Called every frame
//void AItem::Tick(float DeltaTime)
//{
//	Super::Tick(DeltaTime);
//
//}

void AItemActor::Interact(class AProjectTopCharacter* Character)
{
	// Only Destroying on Client isn't good
	// 
	//if (Character)
	//{
	//	Character->AddItemToInventoryWidget(ItemStruct);
	//}
	//Destroy();

	if (HasAuthority() && Character)
	{
		/*Character->AddItemToInventoryWidget(ItemStruct);*/
		Character->AddInventoryItem(ItemStruct);
		Destroy();
	}
}

void AItemActor::ClickItem(AProjectTopCharacter* Character)
{
	UE_LOG(LogTemp, Warning, TEXT("Clicked Item : %s"), *this->GetName());
	UE_LOG(LogTemp, Warning, TEXT("Used from : %s"), *Character->GetName());
}
// Called every frame
//void AItem::Tick(float DeltaTime)
//{
//	Super::Tick(DeltaTime);
//
//}

