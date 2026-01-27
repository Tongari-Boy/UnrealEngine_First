#include "UUserWidget.h"
#include "Components/Button.h"
#include "TutorialSignActor.h"

bool UUUserWidget::Initialize()
{
	if (!Super::Initialize())
	{
		return false;
	}
	if (CloseButton)
	{
		CloseButton->OnClicked.AddDynamic(this, &UUUserWidget::OnCloseClicked);
	}
	return true;
}

void UUUserWidget::SetOwnerActor(ATutorialSignActor* InOwner)
{
	OwnerActor = InOwner;
}

void UUUserWidget::OnCloseClicked()
{
	if (OwnerActor)
	{
		OwnerActor->CloseTutorial();
	}
}