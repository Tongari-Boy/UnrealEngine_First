#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TutorialSignActor.generated.h"

UCLASS()
class MYPROJECT_API ATutorialSignActor : public AActor
{
	GENERATED_BODY()

public:
	ATutorialSignActor();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere,Category="Components")
	class UBoxComponent* TriggerBox;

public:
	void OnInteract();
};
