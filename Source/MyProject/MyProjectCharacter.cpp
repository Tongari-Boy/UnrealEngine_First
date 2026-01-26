#include "MyProjectCharacter.h"

#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"

#include "Blueprint/UserWidget.h"
#include "TutorialSignActor.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

AMyProjectCharacter::AMyProjectCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
		
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);

	/* Camera boom */
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f;
	CameraBoom->bUsePawnControlRotation = true;

	/* Camera */
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom);
	FollowCamera->bUsePawnControlRotation = false;
}

void AMyProjectCharacter::BeginPlay()
{
	Super::BeginPlay();

	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;

	/* Input Mapping Context */
	if (APlayerController* PC = Cast<APlayerController>(GetController()))
	{
		if (ULocalPlayer* LP = PC->GetLocalPlayer())
		{
			if (UEnhancedInputLocalPlayerSubsystem* Subsystem =
				LP->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
			{
				if (DefaultMappingContext)
				{
					Subsystem->AddMappingContext(DefaultMappingContext, 0);
				}
			}
		}
	}

	/* Stamina UI */
	if(StaminaWidgetClass)
	{
		StaminaWidget = CreateWidget<UUserWidget>(GetWorld(), StaminaWidgetClass);
		if (StaminaWidget)
		{
			StaminaWidget->AddToViewport();
		}
	}
}

void AMyProjectCharacter::Tick(float DeltaTime) 
{
	Super::Tick(DeltaTime);

	if (bIsRunning)
	{
		Stamina -= StaminaDrainPerSec * DeltaTime;
		if (Stamina <= 0.f)
		{
			Stamina = 0.f;
			StopRun();
		}
	}
	else
	{
		Stamina += StaminaRecoverPerSec * DeltaTime;
	}

	Stamina = FMath::Clamp(Stamina, 0.f, MaxStamina);
}

void AMyProjectCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Set up action bindings
	if (UEnhancedInputComponent* EIC = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
		// Moving
		EIC->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AMyProjectCharacter::Move);
		// Looking
		EIC->BindAction(LookAction, ETriggerEvent::Triggered, this, &AMyProjectCharacter::Look);
		// Jumping
		EIC->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EIC->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
		// Running
		EIC->BindAction(RunAction, ETriggerEvent::Started, this, &AMyProjectCharacter::StartRun);
		EIC->BindAction(RunAction, ETriggerEvent::Completed, this, &AMyProjectCharacter::StopRun);
		// Interct
		EIC->BindAction(InteractAction, ETriggerEvent::Triggered, this, &AMyProjectCharacter::OnInteract);
	}
}

void AMyProjectCharacter::Move(const FInputActionValue& Value)
{
	const FVector2D Vec = Value.Get<FVector2D>();

	if (!Controller) return;

	const FRotator YawRot(0.f, Controller->GetControlRotation().Yaw, 0.f);

	const FVector Forward = FRotationMatrix(YawRot).GetUnitAxis(EAxis::X);
	const FVector Right = FRotationMatrix(YawRot).GetUnitAxis(EAxis::Y);

	AddMovementInput(Forward, Vec.Y);
	AddMovementInput(Right, Vec.X);
}

void AMyProjectCharacter::Look(const FInputActionValue& Value)
{
	const FVector2D LookAxis = Value.Get<FVector2D>();
	// 左右（Yaw）
	AddControllerYawInput(LookAxis.X);
	// 上下（Pitch）
	AddControllerPitchInput(LookAxis.Y);
}

void AMyProjectCharacter::StartRun()
{
	if (Stamina <= 0.0f)
		return;
	bIsRunning = true;
	GetCharacterMovement()->MaxWalkSpeed = RunSpeed;
}
void AMyProjectCharacter::StopRun()
{
	bIsRunning = false;
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
}

void AMyProjectCharacter::RecoverStamina(float Amount)
{
	Stamina = FMath::Clamp(Stamina + Amount, 0.0f, MaxStamina);
}

void AMyProjectCharacter::OnInteract()
{
	UE_LOG(LogTemp, Warning, TEXT("OnInteract called"));

	if (CurrentSign)
	{
		UE_LOG(LogTemp, Warning, TEXT("OnInteract pressed"));
		CurrentSign->OnInteract();
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("CurrentSign is NULL"));
	}
}

void AMyProjectCharacter::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	UE_LOG(LogTemp, Warning, TEXT("Overlap with: %s"), *GetNameSafe(OtherActor));

	if (ATutorialSignActor* Sign = Cast<ATutorialSignActor>(OtherActor))
	{
		CurrentSign = Sign;
		UE_LOG(LogTemp, Warning, TEXT("TutorialSign detected"));
	}
}
void AMyProjectCharacter::NotifyActorEndOverlap(AActor* OtherActor)
{
	Super::NotifyActorEndOverlap(OtherActor);

	if (OtherActor == CurrentSign)
	{
		CurrentSign = nullptr;
	}
}

float AMyProjectCharacter::GetStaminaPercent() const
{
	return Stamina / MaxStamina;
}
