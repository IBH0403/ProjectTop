// GachaHUD.h

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "GachaHUD.generated.h"

UCLASS()
class AGachaHUD : public AHUD
{
    GENERATED_BODY()

public:
    virtual void DrawHUD() override;

    void ShowMessage(const FString& Message, float DisplayTime);

private:
    FString CurrentMessage;
    float MessageDisplayTime;
    float MessageStartTime;

    UPROPERTY(EditAnywhere, Category = "HUD")
    UFont* HUDFont;
};