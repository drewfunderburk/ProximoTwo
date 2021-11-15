// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

//#include "Runtime/Engine/Public/EngineGlobals.h"
//if (GEngine)
//	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("Output: %f"), amount));

// Sets default values
AFPSCharacter::AFPSCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Autoposess player on play
	AutoPossessPlayer = EAutoReceiveInput::Player0;

	// Enable proper rotation controls
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = true;
	bUseControllerRotationRoll = false;

	// Create and attach camera
	camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	camera->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform);
	camera->SetRelativeLocation(FVector(0, 0, 40));
	camera->bUsePawnControlRotation = true;

	// Initialize default variables
	MouseSensitivity = 1.0f;
	InvertY = false;
	SprintSpeedMultiplier = 2.0f;
	m_BaseWalkSpeed = GetCharacterMovement()->MaxWalkSpeed;
}

// Called when the game starts or when spawned
void AFPSCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFPSCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AFPSCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindAxis("Move X", this, &AFPSCharacter::MoveHorizontal);
	InputComponent->BindAxis("Move Y", this, &AFPSCharacter::MoveVertical);
	InputComponent->BindAxis("Aim X", this, &AFPSCharacter::AimHorizontal);
	InputComponent->BindAxis("Aim Y", this, &AFPSCharacter::AimVertical);
}

void AFPSCharacter::MoveHorizontal(float value)
{
	if (!value) return;

	AddMovementInput(GetActorRightVector(), value);
}

void AFPSCharacter::MoveVertical(float value)
{
	if (!value) return;
	AddMovementInput(GetActorForwardVector(), value);
}

void AFPSCharacter::AimHorizontal(float value)
{
	if (!value) return;
	AddControllerYawInput(value);
}

void AFPSCharacter::AimVertical(float value)
{
	if (!value) return;
	float amount = value;
	if (InvertY)
		amount *= -1;
	AddControllerPitchInput(amount);
}

