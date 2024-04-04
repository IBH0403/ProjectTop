// Fill out your copyright notice in the Description page of Project Settings.

#include "GachaHUD.h"

#include "Engine/Canvas.h"

#include "Kismet/GameplayStatics.h"

#include "Engine/Font.h"

void AGachaHUD::DrawHUD()
{
    Super::DrawHUD();

    if (!CurrentMessage.IsEmpty())
    {
        float CurrentTime = GetWorld()->GetTimeSeconds();
        if (CurrentTime - MessageStartTime <= MessageDisplayTime)
        {
            // 메시지를 화면에 그리기
            float TextWidth = 0.0f;
            float TextHeight = 0.0f;

            if (!HUDFont)
            {
                HUDFont = GEngine->GetLargeFont();
            }

            GetTextSize(CurrentMessage, TextWidth, TextHeight, HUDFont, 1.0f);

            FVector2D MessagePosition((Canvas->ClipX - TextWidth) * 0.5f, (Canvas->ClipY - TextHeight) * 0.5f);
            DrawText(CurrentMessage, FLinearColor::White, MessagePosition.X, MessagePosition.Y, HUDFont, 1.0f, false);
        }
        else
        {
            CurrentMessage.Empty();
        }
    }
}

void AGachaHUD::ShowMessage(const FString& Message, float DisplayTime)

{
    CurrentMessage = Message;
    MessageDisplayTime = DisplayTime;
    MessageStartTime = GetWorld()->GetTimeSeconds();

}