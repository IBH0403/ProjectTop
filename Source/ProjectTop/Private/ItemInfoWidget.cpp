// ItemInfoWidget.cpp


#include "ItemInfoWidget.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Item.h"

void UItemInfoWidget::SetItemInfo(const FItem& DrawnItem)
{
    UTextBlock* ItemNameTextBlock = Cast<UTextBlock>(GetWidgetFromName(TEXT("ItemNameText")));
    if (ItemNameTextBlock != nullptr)
    {
        ItemNameTextBlock->SetText(FText::FromString(DrawnItem.ItemName));
    }

    UTextBlock* ItemGradeTextBlock = Cast<UTextBlock>(GetWidgetFromName(TEXT("ItemGradeText")));
    if (ItemGradeTextBlock != nullptr)
    {
        ItemGradeTextBlock->SetText(FText::AsNumber(DrawnItem.ItemGrade));
    }

    UE_LOG(LogTemp, Warning, TEXT("SetItemInfo called"));
    UE_LOG(LogTemp, Log, TEXT("SetItemInfo called~~~~"));
}