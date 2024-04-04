// Fill out your copyright notice in the Description page of Project Settings.

#include "FireLighter.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"


// Sets default values for this component's properties
UFireLighter::UFireLighter()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UFireLighter::BeginPlay()
{
	Super::BeginPlay();

	UPhysicsHandleComponent* PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (PhysicsHandle != nullptr)
	{
		UE_LOG(LogTemp, Display, TEXT("Got Physics Handle: %s"), *PhysicsHandle->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Display, TEXT("No Physics Handle Found!"));
	}
}


// Called every frame
void UFireLighter::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// FRotator MyRotation = GetComponentRotation();
	// FString RotationString = MyRotation.ToCompactString();
	// UE_LOG(LogTemp, Display, TEXT("Fire Lighter Rotation: %s"), *RotationString);

	// float Time = GetWorld()->TimeSeconds;
	// UE_LOG(LogTemp, Display, TEXT("Current Time Is: %f"), Time);

	AActor* Owner = GetOwner();
	FString Name = Owner->GetActorNameOrLabel();
	FVector OwnerLocation = Owner->GetActorLocation();
	FString OwnerLocationString = OwnerLocation.ToCompactString();

	// UE_LOG(LogTemp, Display, TEXT("FireLigthing to: %s with location %s"), *Name, *OwnerLocationString);

	UPhysicsHandleComponent* PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (PhysicsHandle == nullptr)
	{
		return;
	}

	FVector TargetLocation = GetComponentLocation() + GetForwardVector() * HoldDistance;
	PhysicsHandle->SetTargetLocationAndRotation(TargetLocation, GetComponentRotation());
}

void UFireLighter::Light()
{
	UPhysicsHandleComponent* PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (PhysicsHandle == nullptr)
	{
		//UE_LOG(LogTemp, Display, TEXT("return"));
		return;
	}

	FVector Start = GetComponentLocation();
	FVector End = Start + GetForwardVector() * MaxFireLightDistance;
	// DrawDebugLine(GetWorld(), Start, End, FColor::Blue);
	// 5초 동안 지속
	// DrawDebugSphere(GetWorld(), End, 10, 10, FColor::Black, false, 5);


	FCollisionShape Sphere = FCollisionShape::MakeSphere(FireLightRadius);
	FHitResult HitResult;
	//bool HasHit = GetWorld()->SweepSingleByChannel(
	HasHit = GetWorld()->SweepSingleByChannel(
		HitResult,
		Start, End,
		FQuat::Identity,
		ECC_GameTraceChannel1,
		Sphere
	);


	if (HasHit)
	{
		UE_LOG(LogTemp, Display, TEXT("HitAttempts: %d"), HitAttempts);
		// DrawDebugSphere(GetWorld(), HitResult.Location, 10, 10, FColor::Yellow, false, 5);
		// DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 10, 10, FColor::Purple, false, 5);
		AActor* HitActor = HitResult.GetActor();
		if (HitActor != nullptr) // Good practice to check for nullptr
		{
			UE_LOG(LogTemp, Display, TEXT("Hit actor: %s"), *HitActor->GetActorNameOrLabel());
			PhysicsHandle->GrabComponentAtLocationWithRotation(
				HitResult.GetComponent(),
				NAME_None,
				HitResult.ImpactPoint,
				GetComponentRotation()

			);
		}

		// CallBlueprint();
	}
	// else
	// {
	// 	UE_LOG(LogTemp, Display, TEXT("No actor hit"));
	// }
}

void UFireLighter::Release()
{
	UE_LOG(LogTemp, Display, TEXT("Released lighter"));
}
