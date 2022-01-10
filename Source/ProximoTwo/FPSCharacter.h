// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"

#include "FPSCharacter.generated.h"

struct FCollisionShape;

UCLASS()
class PROXIMOTWO_API AFPSCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFPSCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	UFUNCTION(BlueprintNativeEvent)
	void OnUncrouch();

private:
	void MoveHorizontal(float value);
	void MoveVertical(float value);
	void AimHorizontal(float value);
	void AimVertical(float value);
	void Sprint();
	void UnSprint();
	void Interact();

	UFUNCTION(BlueprintCallable, Category = "FPSCharacter")
	bool CanUncrouch();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
		float MouseSensitivity = 1.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
		bool InvertY = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
		float SprintSpeedMultiplier = 2.0f;

private:
	UPROPERTY(EditAnywhere, Category = "Camera")
	UCameraComponent* camera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FPSCharacter", meta = (AllowPrivateAccess = "true"))
	float interactRange = 250.0f;

	UPROPERTY(BlueprintReadWrite, Category = "FPSCharacter", meta = (AllowPrivateAccess = "true"))
	bool wantsToUncrouch = false;

	UPROPERTY(BlueprintReadOnly, Category = "FPSCharacter", meta = (AllowPrivateAccess = "true"))
	float verticalMoveInputValue = 0.0f;

	UPROPERTY(BlueprintReadOnly, Category = "FPSCharacter", meta = (AllowPrivateAccess = "true"))
	float horizontalMoveInputValue = 0.0f;

	UPROPERTY(BlueprintReadWrite, Category = "FPSCharacter", meta = (AllowPrivateAccess = "true"))
	bool isCrouched = false;

	UPROPERTY(BlueprintReadWrite, Category = "FPSCharacter", meta = (AllowPrivateAccess = "true"))
	float capsuleStartHeight = 0.0f;

	FCollisionShape initialCapsuleCollisionShape;
	float baseWalkSpeed;
};
