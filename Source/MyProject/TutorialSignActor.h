#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UUserWidget.h"
#include "TutorialSignActor.generated.h"

UCLASS()
class MYPROJECT_API ATutorialSignActor : public AActor
{
	GENERATED_BODY()

public:
	//コンストラクタ
	ATutorialSignActor();

	//Eキーでインタラクト
	UFUNCTION(BlueprintCallable,Category = "Tutorial")
	void OnInteract();
	//ウィジェット閉じる
	UFUNCTION(BlueprintCallable, Category = "Tutorial")
	void CloseTutorial();

protected:
	virtual void BeginPlay() override;

	//Trigger Box Component
	UPROPERTY(VisibleAnywhere,Category="Components")
	class UBoxComponent* TriggerBox;

	/* === UI === */
	//Tutorial Widget Class
	UPROPERTY(EditAnywhere, Category = "Tutorial")
	TSubclassOf<UUUserWidget> TutorialWidgetClass;

	//Tutorial Widget Instance
	UPROPERTY()
	UUUserWidget* TutorialWidget;
};
