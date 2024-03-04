// STorch.h

#pragma once

#include "CoreMinimal.h" // Unreal Engine Core ����� ����ϱ� ���� ��� ������ �����մϴ�.
#include "GameFramework/Actor.h" // AActor Ŭ������ ����ϱ� ���� ��� ������ �����մϴ�.
#include "STorch.generated.h" // �ڵ� ������ ��� ������ �����մϴ�.

UCLASS()
class STUDYPROJECT_API ASTorch : public AActor // ASTorch Ŭ������ AActor Ŭ������ ��ӹ����� ��Ÿ���ϴ�.
{
    GENERATED_BODY() // Unreal Engine 4 �ڵ� ���� �ý��ۿ��� �ڵ� ������ �϶�� �����մϴ�.

public:
    ASTorch(); // ������ �����Դϴ�.

    virtual void BeginPlay() override; // �θ� Ŭ������ AActor�� BeginPlay �Լ��� �������մϴ�.

    virtual void Tick(float DeltaSeconds) override; // �θ� Ŭ������ AActor�� Tick �Լ��� �������մϴ�.

private:
    UPROPERTY(VisibleAnywhere) // �ش� ��� ������ ������ �󿡼� ��𿡼��� ���� �������� ��Ÿ���ϴ�.
        TObjectPtr<class UBoxComponent> BoxComponent; // �ڽ� ������Ʈ ��ü�� ���� �������Դϴ�.

    UPROPERTY(VisibleAnywhere) // �ش� ��� ������ ������ �󿡼� ��𿡼��� ���� �������� ��Ÿ���ϴ�.
        TObjectPtr<class UStaticMeshComponent> BodyStaticMeshComponent; // ����ƽ �޽� ������Ʈ ��ü�� ���� �������Դϴ�.

    UPROPERTY(VisibleAnywhere) // �ش� ��� ������ ������ �󿡼� ��𿡼��� ���� �������� ��Ÿ���ϴ�.
        TObjectPtr<class UPointLightComponent> PointLightComponent; // ����Ʈ ����Ʈ ������Ʈ ��ü�� ���� �������Դϴ�.

    UPROPERTY(VisibleAnywhere) // �ش� ��� ������ ������ �󿡼� ��𿡼��� ���� �������� ��Ÿ���ϴ�.
        TObjectPtr<class UParticleSystemComponent> ParticleSystemComponent; // ��ƼŬ �ý��� ������Ʈ ��ü�� ���� �������Դϴ�.

    UPROPERTY(EditAnywhere, category = "ASTorch") // ������ �󿡼� ���� �����ϸ�, ASTorch ī�װ��� �׷�ȭ�˴ϴ�.
        int32 ID; // ��ġ�� ID�� ��Ÿ���� �����Դϴ�.

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "ASTorch", Meta = (AllowPrivateAccess)) // ������ �󿡼� ���� �����ϸ�, ����Ʈ ���� ���� �����ϸ�, �������Ʈ���� �а� ���� �����մϴ�. ASTorch ī�װ��� �׷�ȭ�Ǹ�, private ������ ���˴ϴ�.
        float RotationSpeed; // ��ġ�� ȸ�� �ӵ��� ��Ÿ���� �����Դϴ�.
};
