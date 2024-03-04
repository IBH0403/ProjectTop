// SPigeon.cpp

#include "Examples/SPigeon.h" // SPigeon ��� ������ �����մϴ�.

// USPigeon Ŭ������ ������ �����Դϴ�.
USPigeon::USPigeon()
{
    Name = TEXT("SPigeonCDO"); // Name ��� ������ �ʱ�ȭ�մϴ�.
    ID = 0; // ID ��� ������ �ʱ�ȭ�մϴ�.
}

// Fly �Լ��� �����Դϴ�.
void USPigeon::Fly()
{
    // Unreal Engine �α׸� ����Ͽ� ��ѱⰡ �����ϴ� ���� ����մϴ�.
    UE_LOG(LogTemp, Log, TEXT("%s is now flying."), *Name);
}

// Serialize �Լ��� �����Դϴ�.
void USPigeon::Serialize(FArchive& Ar)
{
    Super::Serialize(Ar); // �θ� Ŭ������ Serialize �Լ��� ȣ���մϴ�.

    Ar << Name; // �̸��� ��ī�̺꿡 ����ȭ�մϴ�.
    Ar << ID; // ID�� ��ī�̺꿡 ����ȭ�մϴ�.
}
