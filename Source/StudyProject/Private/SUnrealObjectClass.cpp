// SUnrealObjectClass.cpp

#include "SUnrealObjectClass.h" // �ش� ��� ������ �����մϴ�.

// USUnrealObjectClass Ŭ������ ������ �����Դϴ�.
USUnrealObjectClass::USUnrealObjectClass()
{
    Name = TEXT("USUnrealObjectClass CDO"); // Name ��� ������ �ʱ�ȭ�մϴ�.
}

// HelloUnreal �Լ��� �����Դϴ�.
void USUnrealObjectClass::HelloUnreal()
{
    // Unreal Engine �α׸� ����մϴ�. LogTemp�� �α��� ī�װ���, �α� ���ؿ� ���� �ٸ��� ó���� �� �ֽ��ϴ�.
    // Log�� �α��� ������ ��Ÿ����, TEXT ��ũ�θ� ����Ͽ� ���ڿ� ���ͷ��� �����մϴ�.
    UE_LOG(LogTemp, Log, TEXT("USUnrealObjectClass::HelloUnreal() has been called."));
}
