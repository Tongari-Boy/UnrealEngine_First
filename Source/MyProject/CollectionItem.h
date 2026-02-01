#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CollectionItem.generated.h"

UCLASS()
class MYPROJECT_API ACollectionItem : public AActor
{
	GENERATED_BODY()
	
public:	
	ACollectionItem();

protected:
	UPROPERTY(VisibleAnywhere)
	class UBoxComponent* collision;

	UPROPERTY(EditAnywhere, Category = "Collect")
	int32 ItemID;

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
