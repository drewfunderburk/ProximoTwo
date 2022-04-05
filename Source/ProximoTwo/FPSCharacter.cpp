// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "DrawDebugHelpers.h"
#include "CollisionShape.h"
#include "Containers/Array.h"
#include "Interactable.h"

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
	FCollisionShape shape = GetCapsuleComponent()->GetCollisionShape();
	initialCapsuleCollisionShape = FCollisionShape::MakeCapsule(shape.GetCapsuleRadius() * 1.05f, shape.GetCapsuleHalfHeight() * 1.05f);
	capsuleStartHeight = GetCapsuleComponent()->GetScaledCapsuleHalfHeight();

}

// Called when the game starts or when spawned
void AFPSCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	baseWalkSpeed = GetCharacterMovement()->MaxWalkSpeed;
}

// Called every frame
void AFPSCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (wantsToUncrouch && CanUncrouch())
	{
		OnUncrouch();
		OnUncrouch_Implementation();
	}
}

// Called to bind functionality to input
void AFPSCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindAxis("Move X", this, &AFPSCharacter::MoveHorizontal);
	InputComponent->BindAxis("Move Y", this, &AFPSCharacter::MoveVertical);
	InputComponent->BindAxis("Aim X", this, &AFPSCharacter::AimHorizontal);
	InputComponent->BindAxis("Aim Y", this, &AFPSCharacter::AimVertical);

	InputComponent->BindAction("Sprint", IE_Pressed, this, &AFPSCharacter::Sprint);
	InputComponent->BindAction("Sprint", IE_Released, this, &AFPSCharacter::UnSprint);

	InputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	InputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	InputComponent->BindAction("Interact", IE_Pressed, this, &AFPSCharacter::Interact);
}

void AFPSCharacter::MoveHorizontal(float value)
{
	horizontalMoveInputValue = value;
	if (!value) return;
	AddMovementInput(GetActorRightVector(), value);
}

void AFPSCharacter::MoveVertical(float value)
{
	verticalMoveInputValue = value;
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

void AFPSCharacter::Sprint()
{
	if (verticalMoveInputValue > 0 && !GetCharacterMovement()->IsCrouching())
		GetCharacterMovement()->MaxWalkSpeed = baseWalkSpeed * SprintSpeedMultiplier;
}

void AFPSCharacter::UnSprint()
{
	GetCharacterMovement()->MaxWalkSpeed = baseWalkSpeed;
}

void AFPSCharacter::Interact()
{
	// Find start and end points for linetrace
	FVector start = camera->GetComponentLocation();
	FVector end = start + camera->GetForwardVector() * interactRange;

	// Linetrace
	FHitResult hit;
	if (GetWorld()->LineTraceSingleByChannel(hit, start, end, ECC_Visibility))
	{
		// If hit actor implements IInteractable, call OnInteract
		if (hit.GetActor()->GetClass()->ImplementsInterface(UInteractable::StaticClass()))
		{
			IInteractable::Execute_OnInteract(hit.GetActor(), GetOwner());
		}
	}
}

bool AFPSCharacter::CanUncrouch()
{
	// Get the capsule component
	UCapsuleComponent* capsule = GetCapsuleComponent();
	
	// Find the difference in half height between the crouched and uncrouched capsule
	float currentHalfHeight = capsule->GetScaledCapsuleHalfHeight();
	float halfHeightDiff = initialCapsuleCollisionShape.GetCapsuleHalfHeight() - currentHalfHeight;

	// Set the location to begin the capsule overlap
	FVector origin = capsule->GetComponentLocation();
	origin.Z += halfHeightDiff;
	
	// Check the shape of the original capsule for collisions
	if (GetWorld()->OverlapBlockingTestByChannel(origin, FQuat::Identity, ECC_Visibility, initialCapsuleCollisionShape))
		return false;
	return true;
}

void AFPSCharacter::OnUncrouch_Implementation()
{
	wantsToUncrouch = false;
}

