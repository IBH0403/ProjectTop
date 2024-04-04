#include "MonsterForThirdFloor.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/DamageType.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"


// Sets default values
AMonsterForThirdFloor::AMonsterForThirdFloor()
{
    // Set this character to call Tick() every frame. You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    // Configure the capsule component for collision and hit events
    GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    GetCapsuleComponent()->SetNotifyRigidBodyCollision(true);
}

// Called when the game starts or when spawned
void AMonsterForThirdFloor::BeginPlay()
{
    Super::BeginPlay();

    // Register the OnHit function to handle hit events
    GetCapsuleComponent()->OnComponentHit.AddDynamic(this, &AMonsterForThirdFloor::OnHit);
}

// Called every frame
void AMonsterForThirdFloor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

// Attack or hit response
void AMonsterForThirdFloor::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
    if (OtherActor && OtherActor != this && bCanAttack)
    {
        // Ensure that OtherActor is not an instance of AMonsterForThirdFloor or any class derived from it
        if (!OtherActor->IsA(AMonsterForThirdFloor::StaticClass()))
        {
            auto MyInstigator = GetInstigatorController();
            auto DamageTypeClass = UDamageType::StaticClass();

            // Apply damage to OtherActor, as it's not a monster
            UGameplayStatics::ApplyDamage(OtherActor, Damage, MyInstigator, this, DamageTypeClass);
        }

        bCanAttack = false;
        GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AMonsterForThirdFloor::ResetAttack, AttackDelay);

    }
}

void AMonsterForThirdFloor::HandleDestruction()
{
    // TODO: Visual/sound effects
    Destroy();

}

void AMonsterForThirdFloor::ResetAttack()
{
    bCanAttack = true;
}
