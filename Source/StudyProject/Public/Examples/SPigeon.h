// SPigeon.h

#pragma once

#include "CoreMinimal.h" // Unreal Engine Core ����� ����ϱ� ���� ��� ������ �����մϴ�.
#include "UObject/NoExportTypes.h" // NoExportTypes Ŭ������ ����ϱ� ���� ��� ������ �����մϴ�.
#include "SFlyable.h" // ��Ŭ��� ������ �׻� .generated.h ���� ���� �ۼ�. // �������̽��� �����ϴ� ��� ������ �׻� .generated.h ���� ���� �ۼ��մϴ�.
#include "SPigeon.generated.h" // �ڵ� ������ ��� ������ �����մϴ�.

/**
 *
 */
UCLASS()
class STUDYPROJECT_API USPigeon // USPigeon Ŭ������ �����մϴ�.
    : public UObject // UObject Ŭ������ ����մϴ�.
    , public ISFlyable // ISFlyable �������̽��� �����մϴ�.
{
    GENERATED_BODY() // Unreal Engine 4 �ڵ� ���� �ý��ۿ��� �ڵ� ������ �϶�� �����մϴ�.

public:
    USPigeon(); // ������ �����Դϴ�.

    virtual void Fly() override; // ISFlyable �������̽��� Fly �Լ��� �����մϴ�.

    const FString& GetName() const { return Name; } // �̸��� ��ȯ�ϴ� �Լ��Դϴ�.

    void SetName(const FString& InName) { Name = InName; } // �̸��� �����ϴ� �Լ��Դϴ�.

    int32 GetID() const { return ID; } // ID�� ��ȯ�ϴ� �Լ��Դϴ�.

    void SetID(int32 InID) { ID = InID; } // ID�� �����ϴ� �Լ��Դϴ�.

    virtual void Serialize(FArchive& Ar) override; // ����ȭ �Լ��� �������մϴ�.

private:
    UPROPERTY() // �ش� ��� ������ ������ �󿡼� ��𿡼��� ���� �������� ��Ÿ���ϴ�.
        FString Name; // �̸��� ��Ÿ���� �����Դϴ�.

    UPROPERTY() // �ش� ��� ������ ������ �󿡼� ��𿡼��� ���� �������� ��Ÿ���ϴ�.
        int32 ID; // ID�� ��Ÿ���� �����Դϴ�.
};
