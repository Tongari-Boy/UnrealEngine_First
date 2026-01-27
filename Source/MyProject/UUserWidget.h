#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UUserWidget.generated.h"

class UButton;

UCLASS()
class MYPROJECT_API UUUserWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual bool Initialize() override;

	UPROPERTY(meta = (BindWidget))
	UButton* CloseButton;

	UFUNCTION()
	void OnCloseClicked();

	/* === 呼び出し === */
public:
	//呼び出し先の設定
	void SetOwnerActor(class ATutorialSignActor* InOwner);

private:
	//呼び出し元のアクター
	UPROPERTY()
	class ATutorialSignActor* OwnerActor;
};
