// SUnrealObjectClass.h

#pragma once

#include "CoreMinimal.h" // Unreal Engine Core ����� ����ϱ� ���� ��� ������ �����մϴ�.
#include "UObject/NoExportTypes.h" // UObject Ŭ������ ����ϱ� ���� ��� ������ �����մϴ�.
#include "SUnrealObjectClass.generated.h" // �ڵ� ������ ��� ������ �����մϴ�.

/**
 *
 */
UCLASS()
class STUDYPROJECT_API USUnrealObjectClass : public UObject // USUnrealObjectClass Ŭ������ UObject Ŭ������ ��ӹ����� ��Ÿ���ϴ�.
{
    GENERATED_BODY() // Unreal Engine 4 �ڵ� ���� �ý��ۿ��� �ڵ� ������ �϶�� �����մϴ�.

public:
    USUnrealObjectClass(); // ������ �����Դϴ�.

    UFUNCTION() // �� �Լ��� Blueprint���� ȣ�� �����ϵ��� �����մϴ�.
        void HelloUnreal(); // Unreal���� ����� �Լ��Դϴ�.

    const FString& GetName() const { return Name; } // Name ������ ���� ��ȯ�ϴ� �Լ��Դϴ�.

public:
    UPROPERTY() // �ش� ��� ������ ������ �󿡼� ��𿡼��� ���� �������� ��Ÿ���ϴ�.
        FString Name; // �̸��� ��Ÿ���� �����Դϴ�.
};
