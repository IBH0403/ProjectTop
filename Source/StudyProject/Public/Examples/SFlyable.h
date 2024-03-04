// SFlyable.h

#pragma once

#include "CoreMinimal.h" // Unreal Engine Core ����� ����ϱ� ���� ��� ������ �����մϴ�.
#include "UObject/Interface.h" // �������̽� Ŭ������ ����ϱ� ���� ��� ������ �����մϴ�.
#include "SFlyable.generated.h" // �ڵ� ������ ��� ������ �����մϴ�.

USTRUCT() // ����ü ������ ���� ��ũ���Դϴ�.
struct FBirdData // FBirdData ����ü�� �����մϴ�.
{
    GENERATED_BODY() // Unreal Engine 4 �ڵ� ���� �ý��ۿ��� �ڵ� ������ �϶�� �����մϴ�.

public:
    FBirdData() {} // �⺻ �������Դϴ�.

    // �̸��� ID�� ���ڷ� �޴� �������Դϴ�.
    FBirdData(const FString& InName, int32 InID)
        : Name(InName)
        , ID(InID)
    {
    }

    // ����ȭ�� ���� ������ �����ε��Դϴ�.
    friend FArchive& operator<<(FArchive& Ar, FBirdData& InBirdData)
    {
        Ar << InBirdData.Name;
        Ar << InBirdData.ID;
        return Ar;
    }

    UPROPERTY() // �ش� ��� ������ ������ �󿡼� ��𿡼��� ���� �������� ��Ÿ���ϴ�.
        FString Name = TEXT("DefaultBirdName"); // ���� �̸��� ��Ÿ���� �����Դϴ�.

    UPROPERTY() // �ش� ��� ������ ������ �󿡼� ��𿡼��� ���� �������� ��Ÿ���ϴ�.
        int32 ID = 0; // ���� ID�� ��Ÿ���� �����Դϴ�.
};

UINTERFACE(MinimalAPI) // �ּ����� API�� ���� �������̽��� �����ϱ� ���� ��ũ���Դϴ�.
class USFlyable : public UInterface // USFlyable �������̽��� �����ϰ� UInterface�� ����մϴ�.
{
    GENERATED_BODY() // Unreal Engine 4 �ڵ� ���� �ý��ۿ��� �ڵ� ������ �϶�� �����մϴ�.
};

/**
 *
 */
class STUDYPROJECT_API ISFlyable // ISFlyable �������̽� Ŭ������ �����մϴ�.
{
    GENERATED_BODY() // Unreal Engine 4 �ڵ� ���� �ý��ۿ��� �ڵ� ������ �϶�� �����մϴ�.

public:
    virtual void Fly() = 0; // ISFlyable���� �����ص� �ǰ� ���ص���. ���ϴ°� ����.
    // Fly �Լ��� ���� ���� �Լ��� �����մϴ�.
    // ISFlyable �������̽��� �����ϴ� Ŭ�������� �ݵ�� �����ؾ� �մϴ�.
    // Fly �Լ��� ������ ISFlyable �������̽��� �����ϴ� Ŭ�������� �ٸ� �� �ֽ��ϴ�.
};
