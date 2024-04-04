// Fill out your copyright notice in the Description page of Project Settings.



//#include "CoreMinimal.h"
//#include "GameFramework/Character.h"
//#include "InventoryCharacter.generated.h"
//
//UCLASS()
//class INVENTORYCPPSTUDY_API AInventoryCharacter : public ACharacter
//{
//	GENERATED_BODY()
//
//public:
//	// Sets default values for this character's properties
//	AInventoryCharacter();
//
//protected:
//	// Called when the game starts or when spawned
//	virtual void BeginPlay() override;
//
//public:	
//	// Called every frame
//	virtual void Tick(float DeltaTime) override;
//
//	// Called to bind functionality to input
//	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
//
//};
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
//#include "Public/Inventory/ItemStructs.h"
#include "../ItemStructs.h"
#include "InventoryCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

struct FItemStruct;
class AItemActor;

//DECLARE_LOG_CATEGORY_EXTERN(LogTemplateInventoryCharacter, Log, All);

UCLASS(config = Game)
class INVENTORYCPPSTUDY_API AInventoryCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;

	/** Inventory Interact Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* InteractAction;


public:
	AInventoryCharacter();


protected:

	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

	/*  Inventory interaction  */
	void Interact();

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void ClickItem(TSubclassOf<AItemActor> ItemSubclass);

	UPROPERTY(BlueprintReadWrite, Category = "Inventory")
	float Health;

	UPROPERTY(BlueprintReadWrite, Category = "Inventory")
	float Hunger;




protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// To add mapping context
	virtual void BeginPlay();

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	UFUNCTION(BlueprintImplementableEvent, Category = "Inventory")
	void AddItemToInventoryWidget(FItemStruct ItemStruct);

	void AddHealth(float Value);

	void RemoveHunger(float Value);
};