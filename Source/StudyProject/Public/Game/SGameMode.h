// SGameMode.h

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SGameMode.generated.h"

/**
 *
 */
UCLASS()
class STUDYPROJECT_API ASGameMode : public AGameModeBase
{
    GENERATED_BODY()

public:
    ASGameMode();

    // ���� �ʱ�ȭ�� �� ȣ��Ǵ� �Լ�.
    virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;

    // ���� ���¸� �ʱ�ȭ�� �� ȣ��Ǵ� �Լ�.
    virtual void InitGameState() override;

    // �α��� ������ ȣ��Ǵ� �Լ�.
    virtual void PreLogin(const FString& Options, const FString& Address, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage) override;

    // ���ο� �÷��̾ �α����� �� ȣ��Ǵ� �Լ�.
    virtual APlayerController* Login(UPlayer* NewPlayer, ENetRole InRemoteRole, const FString& Portal, const FString& Options, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage) override;

    // �÷��̾ ���ӿ� �α��ε� �� ȣ��Ǵ� �Լ�.
    virtual void PostLogin(APlayerController* NewPlayer) override;

    // ������Ʈ �ʱ�ȭ�� �Ϸ�� �� ȣ��Ǵ� �Լ�.
    virtual void PostInitializeComponents() override;
};
