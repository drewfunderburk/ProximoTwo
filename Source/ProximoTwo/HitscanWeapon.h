// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "HitscanWeapon.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROXIMOTWO_API UHitscanWeapon : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHitscanWeapon();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	void Fire();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hitscan Weapon")
	float MaximumRange = 1000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hitscan Weapon")
	float OptimalRange = 500.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hitscan Weapon")
	float FireRate = 3.0f;

private:
	float nextFireTime = 0.0f;
};
