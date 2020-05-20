// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAimingComponent.h"
#include "TankBigBarrel.h"
#include "TankSmallBarrel.h"
#include "Kismet/GameplayStatics.h"
#include "Components/StaticMeshComponent.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UTankAimingComponent::SetBarrelReference(UTankBigBarrel* BigBarrelToSet, UTankSmallBarrel* SmallBarrelToSet)
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

void UTankAimingComponent::Aim(FVector AimingLocation, bool AimingWithBigGun, float BigGunLaunchSpeed, float SmallGunLaunchSpeed)
{
	if (!BigBarrel || !SmallBarrel) { return; }

	FVector OutLaunchVelocity;
	FVector FiringLocation;
	float LaunchSpeed;

	if (AimingWithBigGun)
	{
		FiringLocation = BigBarrel->GetSocketLocation(FName("LaunchPointBig"));
		LaunchSpeed = BigGunLaunchSpeed;
	}
	else 
	{
		FiringLocation = SmallBarrel->GetSocketLocation(FName("LaunchPointSmall"));
		LaunchSpeed = SmallGunLaunchSpeed;
	}

	// This calculates where we need to point our barrel to be able to hit 
	// the point where the crosshair is pointing
	bool HaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(
		this,
		OutLaunchVelocity,
		FiringLocation,
		AimingLocation,
		LaunchSpeed,
		ESuggestProjVelocityTraceOption::DoNotTrace
	);

	if(HaveAimSolution)
	{
		auto AimDirection = OutLaunchVelocity.GetSafeNormal();
		UE_LOG(LogTemp, Warning, TEXT("Aiming at %s"), *AimDirection.ToString());

		MoveBarrel(AimDirection, AimingWithBigGun);
	}
}

void UTankAimingComponent::MoveBarrel(FVector AimDirection, bool AimingWithBigGun)
{
	FRotator BarrelRotation;
	FRotator AimAsRotator = AimDirection.Rotation();
	FRotator DeltaRotator = AimAsRotator - BarrelRotation;

	if (AimingWithBigGun) 
	{ 
		BarrelRotation = BigBarrel->GetForwardVector().Rotation(); 
		BigBarrel->Elevate(5.f);
	}
	else 
	{ 
		BarrelRotation = SmallBarrel->GetForwardVector().Rotation(); 
		SmallBarrel->Elevate(5.f);
	}
}

void UTankAimingComponent::Fire()
{

}