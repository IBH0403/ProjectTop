#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MonsterForThirdFloor.generated.h"

UCLASS()
class PROJECTTOP_API AMonsterForThirdFloor : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMonsterForThirdFloor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Attack occurs Damage
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack")
	float Damage = 50.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack")
	float AttackDelay = 1.37f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack")
	bool bCanAttack = true;

	FTimerHandle TimerHandle;

	// 
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	void Attack(AActor* Target);

	void ResetAttack();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void HandleDestruction();

};
