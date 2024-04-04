#include "HealthComponent.h"
#include "GameFramework/Actor.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"
#include "ThirdFloorGameMode.h"

UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	Health = MaxHealth;
	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::DamageTaken);
	ThirdFloorGameMode = Cast<AThirdFloorGameMode>(UGameplayStatics::GetGameMode(this));
}

void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Your tick-related code here
}

void UHealthComponent::DamageTaken(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* Instigator, AActor* DamageCauser)
{

	if (Damage <= 0.f) return;


	// Take damage
	Health = FMath::Max(Health - Damage, 0.f);
	UE_LOG(LogTemp, Warning, TEXT("OnHit"));
	UE_LOG(LogTemp, Warning, TEXT("%s's current health: %f"), *DamagedActor->GetName(), Health);

	if (Health <= (MaxHealth * 0.3f))
	{
		isUnderThan30Percent = true; 	// the "isUnderThan30Percent" boolean will only apply to BP_GiantLamp

	}
	else if (Health <= 0.f && ThirdFloorGameMode)
	{
		ThirdFloorGameMode->ActorDied(DamagedActor);
	}
	else
	{
		isUnderThan30Percent = false;	// the "isUnderThan30Percent" boolean will only apply to BP_GiantLamp

	}


	// Prevent further damage until the timer expires
	//bCanbeDamaged = false;
	//GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UHealthComponent::ResetAttack, DamageDelay);


}

//void UHealthComponent::ResetAttack()
//{
	//bCanbeDamaged = true;
//}