// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"

#include "FPSCharacter.generated.h"

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

private:
	void MoveHorizontal(float value);
	void MoveVertical(float value);
	void AimHorizontal(float value);
	void AimVertical(float value);

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
		float MouseSensitivity;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
		bool InvertY;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
		float SprintSpeedMultiplier;

private:
	UPROPERTY(EditAnywhere, Category = "Camera")
		UCameraComponent* camera;
	float m_BaseWalkSpeed;
};
