// ItemInfoWidget.h

#pragma once

#include "CoreMinimal.h"
#include "WidgetBlueprint.h"
#include "Blueprint/UserWidget.h"
#include "Item.h"
#include "ItemInfoWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTTOP_API UItemInfoWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
    //UPROPERTY(BlueprintReadWrite)
    //class UTextBlock* ItemNameText;

    //UPROPERTY(BlueprintReadWrite)
    //class UTextBlock* ItemGradeText;

    UFUNCTION(BlueprintCallable)
    void SetItemInfo(const FItem& DrawnItem);

    UFUNCTION(BlueprintImplementableEvent, Category = "UI")
    void OnItemInfoWidgetDisplayed();
};

