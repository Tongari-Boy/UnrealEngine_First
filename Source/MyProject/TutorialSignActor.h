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

	/* === Trigger === */
	UPROPERTY(VisibleAnywhere,Category="Components")
	class UBoxComponent* TriggerBox;


	/* === State === */
	UPROPERTY(VisibleAnywhere, Category = "State")
	bool bCanInteract = false;

	/* === UI === */
	//Tutorial Widget Class
	UPROPERTY(EditAnywhere, Category = "Tutorial")
	TSubclassOf<UUUserWidget> TutorialWidgetClass;

	//Tutorial Widget Instance
	UPROPERTY()
	UUUserWidget* TutorialWidget;

	/* === UI for press E === */

	//press E widget class
	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<UUserWidget> PressEWidgetClass;

	//press E widget instance
	UPROPERTY()
	UUserWidget* PressEWidget;

	/* === Overlap === */

	UFUNCTION()
	void OnTriggerBegin(
		UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult
	);

	UFUNCTION()
	void OnTriggerEnd(
		UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex
	);

};
