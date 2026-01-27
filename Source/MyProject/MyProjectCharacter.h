#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputMappingContext.h"
#include "MyProjectCharacter.generated.h"


class USpringArmComponent;
class UCameraComponent;
class UInputAction;
struct FInputActionValue;
class UUserWidget;
class ATutorialSignActor;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS()
class MYPROJECT_API AMyProjectCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	//Constructor
	AMyProjectCharacter();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	//Initialize input action bindings
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	/* === Components ===*/

	//Camera boom positioning the camera behind the character
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	//Follow camera
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;

	/* === Input Actions === */

	//Enhanced Input Mapping Context
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputMappingContext* DefaultMappingContext;

	//Jump Input Action
	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* JumpAction;

	//Move Input Action
	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* MoveAction;

	//Look Input Action
	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* LookAction;

	//ダッシュ Input Action
	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* RunAction;

	//インタラクト アクション
	UPROPERTY(EditAnywhere,Category = "Input")
	UInputAction* InteractAction;

	/* === Movement === */

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement|Speed")
	float WalkSpeed = 600.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float RunSpeed = 1200.0f;

	bool bIsRunning = false;

	/* === Stamina === */

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stamina")
	float MaxStamina = 100.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Stamina")
	float Stamina = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement|Config")
	float StaminaDrainPerSec = 25.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stamina")
	float StaminaRecoverPerSec = 15.0f;

	UFUNCTION(BlueprintCallable, Category = "Stamina")
	void RecoverStamina(float Amount);

	/* === UI === */

	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<UUserWidget> StaminaWidgetClass;

	UPROPERTY()
	UUserWidget* StaminaWidget;

	/* === Tutorial === */

	UPROPERTY()
	ATutorialSignActor* CurrentSign;

	/* === Input callbacks ===*/

	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);

	void StartRun();
	void StopRun();
	void OnInteract();

	/* === Overlap === */

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	virtual void NotifyActorEndOverlap(AActor* OtherActor) override;

	/* === Stamina UI === */
public:
	UFUNCTION(BlueprintCallable, Category = "Stamina")
	float GetStaminaPercent() const;
};
