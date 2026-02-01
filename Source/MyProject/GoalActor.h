#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GoalActor.generated.h"

UCLASS()
class MYPROJECT_API AGoalActor : public AActor
{
	GENERATED_BODY()

public:
	AGoalActor();

protected:

	UPROPERTY(VisibleAnywhere)
	class UBoxComponent* Collision;

	virtual void BeginPlay() override;

	UFUNCTION()
	void OnOverlap(
		UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult
	);
};