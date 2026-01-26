#include "TutorialSignActor.h"
#include "Components/BoxComponent.h"

ATutorialSignActor::ATutorialSignActor()
{
	PrimaryActorTick.bCanEverTick = false;

	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	RootComponent = TriggerBox;
}

void ATutorialSignActor::BeginPlay()
{
	Super::BeginPlay();
}

void ATutorialSignActor::OnInteract()
{
	UE_LOG(LogTemp, Warning, TEXT("Tutorial Sign Interacted!"));
}
