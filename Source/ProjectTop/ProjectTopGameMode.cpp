// ProjectTopGameMode.cpp

#include "ProjectTopGameMode.h"
#include "ProjectTopCharacter.h"
#include "Public/Item.h"
#include "Public/ItemInfoWidget.h"
#include "Public/GachaHUD.h"
#include "Engine/DataTable.h"
#include <algorithm> // std::find_if 사용
#include "Engine/World.h"
#include "Runtime/LevelSequence/Public/LevelSequenceActor.h"
#include "Runtime/LevelSequence/Public/LevelSequencePlayer.h"
#include "Runtime/LevelSequence/Public/LevelSequence.h"
#include "UObject/ConstructorHelpers.h"

#include "../InventoryCppStudy/Public/Inventory/Save/InventoryState.h"

AProjectTopGameMode::AProjectTopGameMode()
{
	static ConstructorHelpers::FObjectFinder<UDataTable> DataTableAsset(TEXT("/Game/Gacha/DrawTable"));
	DrawResultTable = DataTableAsset.Object;
    HUDClass = AGachaHUD::StaticClass();
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}


void AProjectTopGameMode::PlaySequence(const FString& SequencePath)
{
    UObject* LevelSequenceObject = LoadObject<ULevelSequence>(nullptr, *SequencePath);
    if (!LevelSequenceObject)
    {
        UE_LOG(LogTemp, Warning, TEXT("LevelSequence could not be loaded: %s"), *SequencePath);
        return;
    }

    ULevelSequence* LevelSequence = Cast<ULevelSequence>(LevelSequenceObject);
    if (!LevelSequence)
    {
        UE_LOG(LogTemp, Warning, TEXT("Failed to cast to ULevelSequence: %s"), *SequencePath);
        return;
    }


    UWorld* World = GetWorld();
    if (!World) return;

    // 레벨 시퀀스 액터와 플레이어 생성
    FMovieSceneSequencePlaybackSettings Settings;
    ALevelSequenceActor* LevelSequenceActor;
    LevelSequencePlayer = ULevelSequencePlayer::CreateLevelSequencePlayer(World, LevelSequence, Settings, LevelSequenceActor);

    if (LevelSequencePlayer)
    {
        // 레벨 시퀀스 재생 완료 시 호출될 델리게이트 바인딩
        FScriptDelegate OnFinishedDelegate;
        OnFinishedDelegate.BindUFunction(this, "OnSequenceFinished");
        LevelSequencePlayer->OnFinished.Add(OnFinishedDelegate);

        LevelSequencePlayer->Play();
    }
}

void AProjectTopGameMode::StopSequence()
{
    if (LevelSequencePlayer)
    {
        LevelSequencePlayer->Stop();
        LevelSequencePlayer->OnFinished.Broadcast();
    }
}


FItem AProjectTopGameMode::DrawItemTable(const UDataTable* ItemDataTable)
{
    // 1. 확률에 따라 아이템의 등급 결정
    int32 RandomNum = FMath::RandRange(0, 99);
    int32 Grade = (RandomNum < 60) ? 1 :
        (RandomNum < 85) ? 2 :
        (RandomNum < 97) ? 3 : 4;

    // 2. 결정된 등급의 아이템들 중에서 무작위로 하나 선택
    TArray<FItem*> ItemsOfGrade;
    FString ContextString;
    for (const auto& Row : ItemDataTable->GetRowMap())
    {
        const FItem* Item = (FItem*)Row.Value;
        if (Item && Item->ItemGrade == Grade)
        {
            ItemsOfGrade.Add(const_cast<FItem*>(Item));
        }
    }

    FItem SelectedItem;
    if (!ItemsOfGrade.IsEmpty())
    {
        int32 RandomIndex = FMath::RandRange(0, ItemsOfGrade.Num() - 1);
        SelectedItem = *ItemsOfGrade[RandomIndex]; // 안전한 접근을 위해 IsValidIndex 검사 생략
    }
    else
    {
        // 만약 해당 등급의 아이템이 없으면, 빈 아이템 반환
        return FItem();
    }

    // 3. 아이템 등급에 따라 시퀀스 재생
    switch (SelectedItem.ItemGrade)
    {
    case 1:
        PlaySequence("/Game/Gacha/common");
        break;
    case 2:
        PlaySequence("/Game/Gacha/rare");
        break;
    case 3:
        PlaySequence("/Game/Gacha/epic");
        break;
    case 4:
        PlaySequence("/Game/Gacha/legend");
        break;
    default:
        break;
    }

  /*  AProjectTopCharacter* Character = Cast<AProjectTopCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
    if (Character)
    {
        if (Character->ItemInfoWidgetClass)
        {
            Character->ItemInfoWidget = CreateWidget<UItemInfoWidget>(GetWorld(), Character->ItemInfoWidgetClass);
            if (Character->ItemInfoWidget)
            {
                Character->ItemInfoWidget->SetItemInfo(SelectedItem);
            }
        }
    }*/


    FTimerHandle TimerHandle;
    GetWorldTimerManager().SetTimer(TimerHandle, this, &AProjectTopGameMode::OnSequenceFinished, 0.1f, false);


    return SelectedItem;
}

void AProjectTopGameMode::OnSequenceFinished()
{
    AProjectTopCharacter* Character = Cast<AProjectTopCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
    if (Character)
    {
        //Character->DisplayItemInfoWidget();
        /*Character->DrawItem();*/
    }
}



//Inventory
void AProjectTopGameMode::PostLogin(APlayerController* NewPlayer)
{
    Super::PostLogin(NewPlayer);

    /*ASPlayerState* PlayerState = NewPlayer->GetPlayerState<ASPlayerState>();
    if (true == ::IsValid(PlayerState))
    {
        PlayerState->InitPlayerState();
    }*/
    UE_LOG(LogTemp, Error, TEXT("PostLogin Start"));
    AInventoryState* InventoryState = NewPlayer->GetPlayerState<AInventoryState>();
    if (true == ::IsValid(InventoryState))
    {
        InventoryState->InitInventoryState();
    }

}