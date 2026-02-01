#include "CollectionItem.h"
#include "Components/BoxComponent.h"
#include "MyProjectCharacter.h"

ACollectionItem::ACollectionItem()
{
	PrimaryActorTick.bCanEverTick = false;
	collision = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision"));
	RootComponent = collision;

	collision->SetCollisionProfileName(TEXT("OverlapAll"));
}

void ACollectionItem::BeginPlay()
{
    Super::BeginPlay();
    collision->OnComponentBeginOverlap.AddDynamic(this, &ACollectionItem::OnOverlap);
}

void ACollectionItem::OnOverlap(
    UPrimitiveComponent*,
    AActor* OtherActor,
    UPrimitiveComponent*,
    int32,
    bool,
    const FHitResult&
)

{
    AMyProjectCharacter* Player = Cast<AMyProjectCharacter>(OtherActor);
    if (!Player) return;

    Player->TempCollectedItemIDs.Add(ItemID);

    UE_LOG(LogTemp, Warning, TEXT("Collected Item ID: %d"), ItemID);

    Destroy();
}

