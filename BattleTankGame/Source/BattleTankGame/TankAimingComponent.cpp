// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAimingComponent.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UTankAimingComponent::SetBigBarrelReference(UStaticMeshComponent* BigBarrelToSet, UStaticMeshComponent* SmallBarrelToSet)
{
	BigBarrel = BigBarrelToSet;
	SmallBarrel = SmallBarrelToSet;
}

// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UTankAimingComponent::Aim(FVector AimingLocation, bool AimingWithBigGun)
{
	auto TankName = GetOwner()->GetName();
	auto BigBarrelLocation = BigBarrel->GetComponentLocation().ToString();
	auto SmallBarrelLocation = SmallBarrel->GetComponentLocation().ToString();

	if (AimingWithBigGun)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s is aiming at %s from %s"), *TankName, *AimingLocation.ToString(), *BigBarrelLocation);
	}
	else 
	{
		UE_LOG(LogTemp, Warning, TEXT("%s is aiming at %s from %s"), *TankName, *AimingLocation.ToString(), *SmallBarrelLocation);
	}
}