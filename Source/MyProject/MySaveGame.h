#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "MySaveGame.generated.h"

USTRUCT(BlueprintType)
struct FStageCollectData
{
    GENERATED_BODY()

	//収集済みアイテムIDリスト
	UPROPERTY()
	TSet<int32> CollectedItemIDs;

    UPROPERTY()
    bool bStageUnlocked = false;
};


UCLASS()
class MYPROJECT_API UMySaveGame : public USaveGame
{
	GENERATED_BODY()

public:
	// StageID -> CollectData
	UPROPERTY()
	TMap<FName, FStageCollectData> StageCollectMap;
};

