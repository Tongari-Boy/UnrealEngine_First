#include "GoalActor.h"
#include "Components/BoxComponent.h"
#include "MyprojectCharacter.h"
#include "MySaveGame.h"
#include "Kismet/GameplayStatics.h"

AGoalActor::AGoalActor()
{
    Collision = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision"));
    RootComponent = Collision;

    Collision->SetCollisionProfileName(TEXT("OverlapAll"));
}

void AGoalActor::BeginPlay()
{
    Super::BeginPlay();
    Collision->OnComponentBeginOverlap.AddDynamic(this, &AGoalActor::OnOverlap);
}

void AGoalActor::OnOverlap(
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

    //セーブ or ロード
    UMySaveGame* Save;
    if (UGameplayStatics::DoesSaveGameExist(TEXT("Save"), 0))
    {
        Save = Cast<UMySaveGame>(UGameplayStatics::LoadGameFromSlot(TEXT("Save"), 0));
    }
    else
    {
        Save = Cast<UMySaveGame>(UGameplayStatics::CreateSaveGameObject(UMySaveGame::StaticClass()));
    }

    //ステージデータ取得
    FStageCollectData& Data = Save->StageCollectMap.FindOrAdd(Player->CurrentStageID);

    for (int32 ID : Player->TempCollectedItemIDs)
    {
        Data.CollectedItemIDs.Add(ID);
    }

    Data.bStageUnlocked = true; //次ステージ解放用

    UGameplayStatics::SaveGameToSlot(Save, TEXT("Save"), 0);

    UE_LOG(LogTemp, Warning, TEXT("GOAL! Saved %d items"), Player->TempCollectedItemIDs.Num());
}
