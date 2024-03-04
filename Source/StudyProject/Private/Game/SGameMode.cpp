// SGameMode.cpp

#include "Game/SGameMode.h"
#include "Controllers/SPlayerController.h"
#include "Characters/SPlayerPawn.h"
#include "Characters/SViewCharacter.h"
#include "Game/SPlayerState.h"



ASGameMode::ASGameMode()
{
    // �÷��̾� ��Ʈ�ѷ� Ŭ������ �����մϴ�.
    PlayerControllerClass = ASPlayerController::StaticClass();
    // �⺻ �� Ŭ������ �����մϴ�.
    DefaultPawnClass = ASPlayerPawn::StaticClass();

    /*
    static ConstructorHelpers::FClassFinder<ASViewCharacter> DefaultPlayerCharacterClassRef(TEXT("������Ʈ�н�"));
    if (DefaultPlayerCharacterClassRef.Class)
    {
        DefaultPawnClass = DefaultPlayerCharacterClassRef.Class;
    }
    */

}

void ASGameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
    // ������ �ʱ�ȭ�մϴ�.
    UE_LOG(LogTemp, Error, TEXT("         Start ASGameMode::InitGame()"));
    Super::InitGame(MapName, Options, ErrorMessage);
    UE_LOG(LogTemp, Error, TEXT("         End   ASGameMode::InitGame()"));
}

void ASGameMode::InitGameState()
{
    // ���� ���¸� �ʱ�ȭ�մϴ�.
    UE_LOG(LogTemp, Error, TEXT("         Start ASGameMode::InitGameState()"));
    Super::InitGameState();
    UE_LOG(LogTemp, Error, TEXT("         End   ASGameMode::InitGameState()"));
}

void ASGameMode::PostInitializeComponents()
{
    // ������Ʈ �ʱ�ȭ�� �Ϸ�� �� ����˴ϴ�.
    UE_LOG(LogTemp, Error, TEXT("         Start ASGameMode::PostInitializeComponents()"));
    Super::PostInitializeComponents();
    UE_LOG(LogTemp, Error, TEXT("         End   ASGameMode::PostInitializeComponents()"));
}

void ASGameMode::PreLogin(const FString& Options, const FString& Address, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage)
{
    // �α��� ���� ����˴ϴ�.
    UE_LOG(LogTemp, Error, TEXT("         Start ASGameMode::PreLogin()"));
    Super::PreLogin(Options, Address, UniqueId, ErrorMessage);
    UE_LOG(LogTemp, Error, TEXT("         End   ASGameMode::PreLogin()"));
}

APlayerController* ASGameMode::Login(UPlayer* NewPlayer, ENetRole InRemoteRole, const FString& Portal, const FString& Options, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage)
{
    // �α����� ó���մϴ�.
    UE_LOG(LogTemp, Error, TEXT("         Start ASGameMode::Login()"));
    APlayerController* PlayerController = Super::Login(NewPlayer, InRemoteRole, Portal, Options, UniqueId, ErrorMessage);
    UE_LOG(LogTemp, Error, TEXT("         End   ASGameMode::Login()"));

    return PlayerController;
}

void ASGameMode::PostLogin(APlayerController* NewPlayer)
{
    Super::PostLogin(NewPlayer);

    ASPlayerState* PlayerState = NewPlayer->GetPlayerState<ASPlayerState>();
    if (true == ::IsValid(PlayerState))
    {
        PlayerState->InitPlayerState();
    }
}