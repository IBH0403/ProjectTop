// Copyright Epic Games, Inc. All Rights Reserved.

#include "InventoryCppStudyCharacter.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"

#include "../Public/Inventory/Actors/ItemActor.h"
#include "Inventory/Save/InventoryState.h"
#include "Net/UnrealNetwork.h"

DEFINE_LOG_CATEGORY(LogTemplateInventoryCharacter);

//////////////////////////////////////////////////////////////////////////
// AInventoryCppStudyCharacter

AInventoryCppStudyCharacter::AInventoryCppStudyCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
		
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)


}



void AInventoryCppStudyCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	//Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}


}


//////////////////////////////////////////////////////////////////////////
// Input

void AInventoryCppStudyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
		
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AInventoryCppStudyCharacter::Move);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AInventoryCppStudyCharacter::Look);

		// Interact Inventory
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Triggered, this, &AInventoryCppStudyCharacter::Interact);

	}
	else
	{
		//UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void AInventoryCppStudyCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME_CONDITION(AInventoryCppStudyCharacter, InventoryItems, COND_OwnerOnly);
}

void AInventoryCppStudyCharacter::CheckInventory(TArray<FItemStruct> Items)
{
	UE_LOG(LogTemp, Warning, TEXT("CheckInventory"));
	int32 count = 0;
	for (FItemStruct item : Items)
	{
		float temp = item.ItemCost;
		UE_LOG(LogTemp, Warning, TEXT("current itemcost %d : %f"), count++, temp);
	}
}

void AInventoryCppStudyCharacter::OnDeleteItemFromInventory()
{
	AInventoryState* InventoryState = Cast<AInventoryState>(this->GetPlayerState());
	if (true == ::IsValid(InventoryState))
	{
		InventoryState->SetInventoryItems(InventoryItems);
	}
}



void AInventoryCppStudyCharacter::OnRep_InventoryItems()
{
	if (InventoryItems.Num())
	{
		//AddItemToInventoryWidget(InventoryItems[InventoryItems.Num() - 1]);
		AddItemToInventoryWidget(AddingItem);

		AInventoryState* InventoryState = Cast<AInventoryState>(this->GetPlayerState());
		if (true == :: IsValid(InventoryState))
		{
			InventoryState->SetInventoryItems(InventoryItems);
		}
		
	}
	
}

void AInventoryCppStudyCharacter::AddInventoryItem(FItemStruct ItemStruct)
{
	if (HasAuthority())
	{
		//InventoryItems.Add(ItemStruct);
		AddingItem = ItemStruct;
		

		if (IsLocallyControlled())
		{
			OnRep_InventoryItems();
		}
		
	}


}


void AInventoryCppStudyCharacter::UpdateStats_Implementation(float HungerValue, float HpValue)
{
}


// ** Original Interact **
//void AInventoryCppStudyCharacter::Interact()
//{
//	// Interaction based on Follow Camera.
//	FVector Start = FollowCamera->GetComponentLocation();
//	FVector End = Start + FollowCamera->GetForwardVector() * 500.0f;
//
//
//	// Interaction based on Character
//	//FVector Start = this->GetActorLocation();
//	//FVector End = Start + this->GetActorForwardVector() * 500.0f;
//
//	FCollisionQueryParams Params;
//	Params.AddIgnoredActor(this);
//
//	FHitResult HitResult;
//	if (GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECollisionChannel::ECC_Visibility, Params))
//	{
//		if (AActor* Actor = HitResult.GetActor())
//		{
//			UE_LOG(LogTemp, Warning, TEXT("Hit Actor : %s"), *Actor->GetName());
//		}
//		else
//		{
//			UE_LOG(LogTemp, Warning, TEXT("is not a actor???"), *Actor->GetName());
//		}
//
//		if (IInteractableInterface* Interface = Cast<IInteractableInterface>(HitResult.GetActor()))
//		{
//			Interface->Interact(this);
//			UE_LOG(LogTemp, Warning, TEXT("Interact success"));
//		}
//		else
//		{
//			UE_LOG(LogTemp, Warning, TEXT("Interact failed"));
//		}
//	}
//	else
//	{
//		UE_LOG(LogTemp, Warning, TEXT("Nothing Hit"));
//	}
//}
void AInventoryCppStudyCharacter::Interact()
{
	// Interaction based on Follow Camera.
	FVector Start = FollowCamera->GetComponentLocation();
	FVector End = Start + FollowCamera->GetForwardVector() * 500.0f;

	if (HasAuthority())
	{
		Interact(Start, End);
	}
	else
	{
		Server_Interact(Start, End);
	}

}
void AInventoryCppStudyCharacter::Interact(FVector Start, FVector End)
{
	// Interaction based on Character
	//FVector Start = this->GetActorLocation();
	//FVector End = Start + this->GetActorForwardVector() * 500.0f;

	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);

	FHitResult HitResult;
	if (GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECollisionChannel::ECC_Visibility, Params))
	{
		if (AActor* Actor = HitResult.GetActor())
		{
			UE_LOG(LogTemp, Warning, TEXT("Hit Actor : %s"), *Actor->GetName());
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("is not a actor???"), *Actor->GetName());
		}

		if (IInteractableInterface* Interface = Cast<IInteractableInterface>(HitResult.GetActor()))
		{
			Interface->Interact(this);
			UE_LOG(LogTemp, Warning, TEXT("Interact success"));
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Interact failed"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Nothing Hit"));
	}
}



void AInventoryCppStudyCharacter::Server_Interact_Implementation(FVector Start, FVector End)
{
	Interact(Start, End);
}

bool AInventoryCppStudyCharacter::Server_Interact_Validate(FVector Start, FVector End)
{
	return true;
}


void AInventoryCppStudyCharacter::ClickItem(TSubclassOf<AItemActor> ItemSubclass)
{
	if (ItemSubclass)
	{
		if (AItemActor* Item = ItemSubclass.GetDefaultObject())
		{
			Item->ClickItem(this);
			UE_LOG(LogTemp, Warning, TEXT("OKay, let's delete it"));

		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Failed getting CDO"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed getting Item"));
	}
}




void AInventoryCppStudyCharacter::AddHp(float Value)
{
	Hp += Value;
	UpdateStats(Hunger, Hp);
	UE_LOG(LogTemp, Warning, TEXT("Added Health : %f"), Value);
}

void AInventoryCppStudyCharacter::RemoveHunger(float Value)
{
	Hunger -= Value;
	UpdateStats(Hunger, Hp);
	UE_LOG(LogTemp, Warning, TEXT("Removed Hunger : %f"), Value);
}




void AInventoryCppStudyCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	
		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void AInventoryCppStudyCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}


