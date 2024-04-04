// ProjectTopCharacter.h

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "Public/ItemInfoWidget.h"
#include "Public/GachaHUD.h"
#include "../InventoryCppStudy/Public/Inventory/ItemStructs.h"
#include "ProjectTopCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;


//====Inventory=======
struct FItemStruct;
class AItemActor;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS(config=Game)
class PROJECTTOP_API AProjectTopCharacter : public ACharacter
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

	/** Draw Item Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* DrawItemAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* StopSequenceAction;


	//======Inventory========
	/** Inventory Interact Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* InteractAction;

	

public:
	AProjectTopCharacter();

	UPROPERTY(BlueprintReadWrite)
	UItemInfoWidget* ItemInfoWidget;

	UFUNCTION(BlueprintCallable, Category = "UI")
	void DisplayItemInfoWidget();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
	TSubclassOf<UItemInfoWidget> ItemInfoWidgetClass;

	UFUNCTION(BlueprintCallable)
	void CreateItemInfoWidget(const FItem& DrawnItem);

	void ShowMessage(const FString& Message, float DisplayTime);

	UFUNCTION(BlueprintCallable, Category = "draw")
	void DrawItem();

	void StartDrawing();

protected:

	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

	void StopSequence();


	//=======Inventory
	/*  Inventory interaction  */
	void Interact();
	void Interact(FVector Start, FVector End);
	UFUNCTION(Server, Reliable, WithValidation)
	void Server_Interact(FVector Start, FVector End);


	UFUNCTION(BlueprintNativeEvent, Category = "Inventory")
	void UpdateStats(float HungerValue, float HpValue);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void ClickItem(TSubclassOf<AItemActor> ItemSubclass);

	UPROPERTY(BlueprintReadWrite, Category = "Inventory")
	float Hp;

	UPROPERTY(BlueprintReadWrite, Category = "Inventory")
	float Hunger;

	UPROPERTY(BlueprintReadWrite, Category = "Inventory")
	FItemStruct AddingItem;

	UPROPERTY(ReplicatedUsing = OnRep_InventoryItems, BlueprintReadWrite, Category = "Inventory")
	TArray<FItemStruct> InventoryItems;
	UFUNCTION()
	void OnRep_InventoryItems();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION(BlueprintImplementableEvent, Category = "Inventory")
	void AddItemToInventoryWidget(FItemStruct ItemStruct);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void CheckInventory(TArray<FItemStruct> Items);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void OnDeleteItemFromInventory();

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



	//=========Inventory===========
	void AddHp(float Value);

	void RemoveHunger(float Value);

	void AddInventoryItem(FItemStruct ItemStruct);
};

