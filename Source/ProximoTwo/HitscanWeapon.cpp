// Fill out your copyright notice in the Description page of Project Settings.


#include "HitscanWeapon.h"

// Sets default values for this component's properties
UHitscanWeapon::UHitscanWeapon()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UHitscanWeapon::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UHitscanWeapon::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UHitscanWeapon::Fire()
{
	// Don't fire if fire rate is not met
	if (GetWorld()->GetTimeSeconds() < nextFireTime)
		return;

	nextFireTime = GetWorld()->GetTimeSeconds() + (1 / FireRate);

	
}

