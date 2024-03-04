// STorch.cpp

#include "WorldStatics/STorch.h" // STorch ��� ������ �����մϴ�.
#include "Components/BoxComponent.h" // �ڽ� ������Ʈ ��� ������ �����մϴ�.
#include "Components/PointLightComponent.h" // ����Ʈ ����Ʈ ������Ʈ ��� ������ �����մϴ�.
#include "Particles/ParticleSystemComponent.h" // ��ƼŬ �ý��� ������Ʈ ��� ������ �����մϴ�.

ASTorch::ASTorch()
{
    PrimaryActorTick.bCanEverTick = true; // �ֱ������� Tick �Լ��� ȣ��ǵ��� �����մϴ�.

    // Box ������Ʈ�� �����ϰ� ��Ʈ ������Ʈ�� �����մϴ�.
    BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
    SetRootComponent(BoxComponent);

    // �ٵ� ����ƽ �޽� ������Ʈ�� �����ϰ� Box ������Ʈ�� �����մϴ�.
    BodyStaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BodyStaticMeshComponent"));
    BodyStaticMeshComponent->SetupAttachment(GetRootComponent());
    BodyStaticMeshComponent->SetRelativeLocation(FVector(0.f, 0.f, -30.f));
    // Pillar_50x500 ����ƽ �޽ø� �ҷ��ͼ� �ٵ� ����ƽ �޽� ������Ʈ�� �����մϴ�.
    static ConstructorHelpers::FObjectFinder<UStaticMesh> BodyStaticMesh(TEXT("/Script/Engine.StaticMesh'/Game/StarterContent/Architecture/Pillar_50x500.Pillar_50x500'"));
    // ��� ������ �÷��� �߿��� ������� �����Ƿ�, static Ű���� ���.
    if (true == BodyStaticMesh.Succeeded())
    {
        BodyStaticMeshComponent->SetStaticMesh(BodyStaticMesh.Object);
    }

    // ����Ʈ ����Ʈ ������Ʈ�� �����ϰ� Box ������Ʈ�� �����մϴ�.
    PointLightComponent = CreateDefaultSubobject<UPointLightComponent>(TEXT("PointLightComponent"));
    PointLightComponent->SetupAttachment(GetRootComponent());
    PointLightComponent->SetRelativeLocation(FVector(0.f, 0.f, 500.f));

    // ��ƼŬ �ý��� ������Ʈ�� �����ϰ� Box ������Ʈ�� �����մϴ�.
    ParticleSystemComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ParticleSystemComponent"));
    ParticleSystemComponent->SetupAttachment(GetRootComponent());
    ParticleSystemComponent->SetRelativeLocation(FVector(0.f, 0.f, 500.f));
    // ���̾� ��ƼŬ ���ø��� �ҷ��ͼ� ��ƼŬ �ý��� ������Ʈ�� �����մϴ�.
    static ConstructorHelpers::FObjectFinder<UParticleSystem> ParticleTemplate(TEXT("/Script/Engine.ParticleSystem'/Game/StarterContent/Particles/P_Fire.P_Fire'"));
    if (true == ParticleTemplate.Succeeded())
    {
        ParticleSystemComponent->SetTemplate(ParticleTemplate.Object);
    }
}

void ASTorch::BeginPlay()
{
    Super::BeginPlay(); // �θ� Ŭ������ BeginPlay �Լ��� ȣ���մϴ�.

    RotationSpeed = 300.f; // ȸ�� �ӵ��� �ʱ�ȭ�մϴ�.
}

void ASTorch::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds); // �θ� Ŭ������ Tick �Լ��� ȣ���մϴ�.

    // Torch�� ȸ����Ű�� �ڵ��Դϴ�.
    AddActorWorldRotation(FRotator(0.f, RotationSpeed * DeltaSeconds, 0.f));
}
