// ProjectTopCharacter.cpp

#include "ProjectTopCharacter.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Public/Item.h"
#include "Public/ItemInfoWidget.h"
#include "Public/GachaHUD.h"
#include "Blueprint/UserWidget.h"
#include "ProjectTopGameMode.h"
#include "Widgets/SWindow.h"
#include "Framework/Application/SlateApplication.h"
#include "Kismet/GameplayStatics.h"

//#include "../InventoryCppStudy/Public/Inventory/Actors/ItemActor.h"
#include "InventoryCppStudy/Public/Inventory/Actors/ItemActor.h"
#include "InventoryCppStudy/Public/Inventory/Save/InventoryState.h"
#include "Net/UnrealNetwork.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

//////////////////////////////////////////////////////////////////////////
// AProjectTopCharacter

AProjectTopCharacter::AProjectTopCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
	ItemInfoWidgetClass = UItemInfoWidget::StaticClass();
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
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controllerb 

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)
}

void AProjectTopCharacter::BeginPlay()
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

void AProjectTopCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
		
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AProjectTopCharacter::Move);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AProjectTopCharacter::Look);

		// Draw
		EnhancedInputComponent->BindAction(DrawItemAction, ETriggerEvent::Triggered, this, &AProjectTopCharacter::StartDrawing);

		EnhancedInputComponent->BindAction(StopSequenceAction, ETriggerEvent::Triggered, this, &AProjectTopCharacter::StopSequence);


		//========Inventory=======
		// Interact Inventory
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Triggered, this, &AProjectTopCharacter::Interact);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void AProjectTopCharacter::Move(const FInputActionValue& Value)
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

void AProjectTopCharacter::Look(const FInputActionValue& Value)
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


void AProjectTopCharacter::StopSequence()
{
	AProjectTopGameMode* GameMode = Cast<AProjectTopGameMode>(GetWorld()->GetAuthGameMode());
	if (GameMode)
	{
		GameMode->StopSequence();
	}
}

void AProjectTopCharacter::CreateItemInfoWidget(const FItem& DrawnItem)
{
	if (ItemInfoWidgetClass != nullptr)
	{
		UWorld* World = GetWorld();
		if (World != nullptr)
		{
			APlayerController* PlayerController = World->GetFirstPlayerController();
			if (PlayerController != nullptr)
			{
				ItemInfoWidget = CreateWidget<UItemInfoWidget>(PlayerController, ItemInfoWidgetClass);
				if (ItemInfoWidget != nullptr)
				{
					ItemInfoWidget->SetItemInfo(DrawnItem);
					ItemInfoWidget->AddToViewport();
					GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("ItemInfoWidget created and added to viewport"));
				}
				else
				{
					GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Failed to create ItemInfoWidget"));
				}
			}
			else
			{
				GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("PlayerController is null"));
			}
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("World is null"));
		}
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("ItemInfoWidgetClass is null"));
	}
}
//
//void AProjectTopCharacter::CreateItemInfoWidget(const FItem& DrawnItem)
//{
//	//if (ItemInfoWidgetClass != nullptr)
//	//{
//	//	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("createwidget1"));
//		//if (ItemInfoWidget == nullptr)
//		//{
//			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("create2"));
//			ItemInfoWidget = CreateWidget<UItemInfoWidget>(GetWorld(), ItemInfoWidgetClass);
//		//}
//
//		//if (ItemInfoWidget != nullptr)
//		//{
//			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("create3"));
//			ItemInfoWidget->SetItemInfo(DrawnItem);
//	//	}
//	//}
//}

void AProjectTopCharacter::DisplayItemInfoWidget()
{
	if (ItemInfoWidget != nullptr)
	{
		ItemInfoWidget->AddToViewport();
		ItemInfoWidget->OnItemInfoWidgetDisplayed();
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("ItemInfoWidget displayed"));
		UE_LOG(LogTemp, Log, TEXT("Log Message1234"));
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("ItemInfoWidget is null in DisplayItemInfoWidget"));
	}
}
//
//void AProjectTopCharacter::DisplayItemInfoWidget()
//{
//	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("display1"));
//	if (ItemInfoWidget != nullptr)
//	{
//		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("display2"));
//		if (!ItemInfoWidget->IsInViewport())
//		{
//			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("display3"));
//			ItemInfoWidget->AddToViewport();
//		}
//		ItemInfoWidget->OnItemInfoWidgetDisplayed();
//
//	}
//}

void ShowPopupMessage(const FString& Message, const FString& Title)
{
	FText MessageText = FText::FromString(Message);
	FText TitleText = FText::FromString(Title);

	FMessageDialog::Open(EAppMsgType::Ok, MessageText, &TitleText);
}
void AProjectTopCharacter::ShowMessage(const FString& Message, float DisplayTime)
{
	AGachaHUD* GachaHUD = Cast<AGachaHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
	if (GachaHUD)
	{
		GachaHUD->ShowMessage(Message, DisplayTime);
	}
}

//void AProjectTopCharacter::DrawItem()
//{
//	// DrawItemTable 함수 호출하여 아이템 뽑기
//	AProjectTopGameMode* GameMode = Cast<AProjectTopGameMode>(GetWorld()->GetAuthGameMode());
//	if (GameMode)
//	{
//		FItem DrawnItem = GameMode->DrawItemTable(GameMode->DrawResultTable);
//		CreateItemInfoWidget(DrawnItem);
//		// 뽑힌 아이템 정보 출력
//		if (DrawnItem.ItemName.IsEmpty())
//		{
//			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("No item drawn!"));
//		}
//		else
//		{
//			FString ItemInfo = FString::Printf(TEXT("Drawn Item: %s (Grade %d)"), *DrawnItem.ItemName, DrawnItem.ItemGrade);
//			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, *ItemInfo);
//		}
//		DisplayItemInfoWidget();
//		if (DrawnItem.ItemName.IsEmpty())
//		{
//			ShowPopupMessage("No item drawn!", "Draw Result");
//		}
//		else
//		{
//			FString ItemInfo = FString::Printf(TEXT("Drawn Item: %s (Grade %d)"), *DrawnItem.ItemName, DrawnItem.ItemGrade);
//			/*ShowPopupMessage(ItemInfo, "Draw Result");*/
//			ShowMessage(ItemInfo, 5.0f);
//		}
//
//	}
//}
void AProjectTopCharacter::StartDrawing()
{
	// 뽑기 시작 시 DrawItem 함수 호출
	DrawItem();
}

void AProjectTopCharacter::DrawItem()
{
	// DrawItemTable 함수 호출하여 아이템 뽑기
	AProjectTopGameMode* GameMode = Cast<AProjectTopGameMode>(GetWorld()->GetAuthGameMode());
	if (GameMode)
	{
		FItem DrawnItem = GameMode->DrawItemTable(GameMode->DrawResultTable);

		// 뽑힌 아이템 정보 출력
		if (DrawnItem.ItemName.IsEmpty())
		{
			// 아이템 뽑기 실패 시 HUD에 메시지 표시
			ShowMessage("No item drawn!", 3.0f);
		}
		else
		{
			// 아이템 뽑기 성공 시 HUD에 메시지 표시
			FString ItemInfo = FString::Printf(TEXT("Drawn Item: %s (Grade %d)"), *DrawnItem.ItemName, DrawnItem.ItemGrade);
			ShowMessage(ItemInfo, 5.0f);
		}
	}
}



//========Inventory ============
void AProjectTopCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME_CONDITION(AProjectTopCharacter, InventoryItems, COND_OwnerOnly);
}

void AProjectTopCharacter::CheckInventory(TArray<FItemStruct> Items)
{
	UE_LOG(LogTemp, Warning, TEXT("CheckInventory"));
	int32 count = 0;
	for (FItemStruct item : Items)
	{
		float temp = item.ItemCost;
		UE_LOG(LogTemp, Warning, TEXT("current itemcost %d : %f"), count++, temp);
	}
}

void AProjectTopCharacter::OnDeleteItemFromInventory()
{
	AInventoryState* InventoryState = Cast<AInventoryState>(this->GetPlayerState());
	if (true == ::IsValid(InventoryState))
	{
		InventoryState->SetInventoryItems(InventoryItems);
	}
}

void AProjectTopCharacter::OnRep_InventoryItems()
{
	if (InventoryItems.Num())
	{
		//AddItemToInventoryWidget(InventoryItems[InventoryItems.Num() - 1]);
		AddItemToInventoryWidget(AddingItem);

		AInventoryState* InventoryState = Cast<AInventoryState>(this->GetPlayerState());
		if (true == ::IsValid(InventoryState))
		{
			InventoryState->SetInventoryItems(InventoryItems);
		}

	}

}

void AProjectTopCharacter::AddInventoryItem(FItemStruct ItemStruct)
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


void AProjectTopCharacter::UpdateStats_Implementation(float HungerValue, float HpValue)
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
void AProjectTopCharacter::Interact()
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
void AProjectTopCharacter::Interact(FVector Start, FVector End)
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



void AProjectTopCharacter::Server_Interact_Implementation(FVector Start, FVector End)
{
	Interact(Start, End);
}

bool AProjectTopCharacter::Server_Interact_Validate(FVector Start, FVector End)
{
	return true;
}


void AProjectTopCharacter::ClickItem(TSubclassOf<AItemActor> ItemSubclass)
{
	if (ItemSubclass)
	{
		if (AItemActor* Item = ItemSubclass.GetDefaultObject())
		{
			Item->ClickItem(this);
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




void AProjectTopCharacter::AddHp(float Value)
{
	Hp += Value;
	UpdateStats(Hunger, Hp);
	UE_LOG(LogTemp, Warning, TEXT("Added Health : %f"), Value);
}

void AProjectTopCharacter::RemoveHunger(float Value)
{
	Hunger -= Value;
	UpdateStats(Hunger, Hp);
	UE_LOG(LogTemp, Warning, TEXT("Removed Hunger : %f"), Value);
}