// Fill out your copyright notice in the Description page of Project Settings.


#include "ClearThirdFloor.h"
#include "Math/UnrealMathUtility.h"

// Sets default values for this component's properties
UClearThirdFloor::UClearThirdFloor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UClearThirdFloor::BeginPlay()
{
	Super::BeginPlay();

	OriginalLocation = GetOwner()->GetActorLocation();

}


// Called every frame
void UClearThirdFloor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	AActor* Owner = GetOwner();
	FString Name = Owner->GetActorNameOrLabel();
	FVector OwnerLocation = Owner->GetActorLocation();
	FString OwnerLocationString = OwnerLocation.ToCompactString();

	//UE_LOG(LogTemp, Display, TEXT("Mover Owner: %s with location %s"), *Name, *OwnerLocationString);

	if (DoorOpen)
	{
		FVector CurrentLocation = GetOwner()->GetActorLocation();
		FVector TargetLocation = OriginalLocation + MoveOffset;
		float MoveSpeed = FVector::Distance(OriginalLocation, TargetLocation) / MoveTime;

		FVector NewLocation = FMath::VInterpConstantTo(CurrentLocation, TargetLocation, DeltaTime, MoveSpeed);
		GetOwner()->SetActorLocation(NewLocation);

		// Optionally, handle rotation
		FRotator CurrentRotation = GetOwner()->GetActorRotation();
		FRotator NewRotation = FMath::RInterpConstantTo(CurrentRotation, TargetRotation, DeltaTime, RotationSpeed);
		GetOwner()->SetActorRotation(NewRotation);
	}
}