#include "TutorialSignActor.h"
#include "Components/BoxComponent.h"
#include "Blueprint/UserWidget.h"
#include "GameFramework/PlayerController.h"

ATutorialSignActor::ATutorialSignActor()
{
	PrimaryActorTick.bCanEverTick = false;

	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	RootComponent = TriggerBox;

	TriggerBox->SetCollisionProfileName(TEXT("Trigger"));
	TriggerBox->SetGenerateOverlapEvents(true);

	//Overlap Events設定
	TriggerBox->SetGenerateOverlapEvents(true);
	TriggerBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	TriggerBox->SetCollisionResponseToAllChannels(ECR_Ignore);
	TriggerBox->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

	TriggerBox->OnComponentBeginOverlap.AddDynamic(
		this, &ATutorialSignActor::OnTriggerBegin
	);

	TriggerBox->OnComponentEndOverlap.AddDynamic(
		this, &ATutorialSignActor::OnTriggerEnd
	);
}

void ATutorialSignActor::BeginPlay()
{
	Super::BeginPlay();
}

void ATutorialSignActor::OnInteract()
{
	if (!bCanInteract) return;

	if (PressEWidget)
	{
		PressEWidget->RemoveFromParent();
	}

	APlayerController* PC = GetWorld()->GetFirstPlayerController();
	if (!PC) return;

	//Widgetが存在しない->Widgetを作成
	if (!TutorialWidget && TutorialWidgetClass) 
	{
		TutorialWidget = CreateWidget<UUUserWidget>(
			PC,
			TutorialWidgetClass
		);

		if (TutorialWidget)
		{
			TutorialWidget->SetOwnerActor(this);
		}
	}

	//WidgetがViewportに存在しない->Viewportに追加
	if (TutorialWidget && !TutorialWidget->IsInViewport()) 
	{
		TutorialWidget->AddToViewport();

		/* === 操作をUIに切り替え === */
		//ゲームモードの操作
		PC->SetIgnoreMoveInput(true);
		PC->SetIgnoreLookInput(true);

		//UIモードの操作
		FInputModeUIOnly InputMode;
		InputMode.SetWidgetToFocus(TutorialWidget->TakeWidget());
		InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
		PC->SetInputMode(InputMode);
		PC->bShowMouseCursor = true;
	}

	UE_LOG(LogTemp, Warning, TEXT("Tutorial Sign Interacted!"));
}

void ATutorialSignActor::CloseTutorial()
{
	UE_LOG(LogTemp, Warning, TEXT("Uhyoman was here..."));
	APlayerController* PC = GetWorld()->GetFirstPlayerController();
	if (!PC) return;

	if (TutorialWidget)
	{
		TutorialWidget->RemoveFromParent();
	}

	/* === 操作をゲームに切り替え === */
	//ゲームモードの操作
	PC->SetIgnoreMoveInput(false);
	PC->SetIgnoreLookInput(false);
	//ゲームモードの操作
	FInputModeGameOnly InputMode;
	PC->SetInputMode(InputMode);
	PC->bShowMouseCursor = false;

	UE_LOG(LogTemp, Warning, TEXT("Tutorial Sign Closed!"));
}

void ATutorialSignActor::OnTriggerBegin(
	UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult
)
{
	if (!OtherActor || OtherActor != GetWorld()->GetFirstPlayerController()->GetPawn())
		return;

	//Press E 表示
	if (!PressEWidget && PressEWidgetClass)
	{
		PressEWidget = CreateWidget<UUserWidget>(
			GetWorld(),
			PressEWidgetClass
		);
	}

	if (PressEWidget && !PressEWidget->IsInViewport())
	{
		PressEWidget->AddToViewport();
	}

	bCanInteract = true;
}

void ATutorialSignActor::OnTriggerEnd(
	UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex
)
{
	if (!OtherActor || OtherActor != GetWorld()->GetFirstPlayerController()->GetPawn())
		return;

	if (PressEWidget)
	{
		PressEWidget->RemoveFromParent();
	}

	bCanInteract = false;
}
