// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAimingComponent.h"
#include "TankBigBarrel.h"
#include "TankSmallBarrel.h"
#include "BigTurret.h"
#include "SmallTurret.h"
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

void UTankAimingComponent::SetTurretReference(UBigTurret* BigTurretToSet, USmallTurret* SmallTurretToSet)
{
	BigTurret = BigTurretToSet;
	SmallTurret = SmallTurretToSet;
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
	if (!BigBarrel || !SmallBarrel || !BigTurret ||!SmallTurret) { return; }

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
		false,
		0,
		0,
		ESuggestProjVelocityTraceOption::DoNotTrace
	);

	if(HaveAimSolution)
	{
		auto AimDirection = OutLaunchVelocity.GetSafeNormal();

		MoveBarrelAndTurret(AimDirection, AimingWithBigGun);
	}
	else 
	{
		UE_LOG(LogTemp, Warning, TEXT("No aiming solution found"));
	}
}

void UTankAimingComponent::MoveBarrelAndTurret(FVector AimDirection, bool AimingWithBigGun)
{
	FRotator BarrelRotation;
	FRotator TurretRotation;

	FRotator AimAsRotator = AimDirection.Rotation();

	FRotator DeltaRotatorBarrel;
	FRotator DeltaRotatorTurret;

	if (AimingWithBigGun) 
	{ 
		BarrelRotation = BigBarrel->GetForwardVector().Rotation();
		TurretRotation = BigTurret->GetForwardVector().Rotation();

		DeltaRotatorBarrel = AimAsRotator - BarrelRotation;
		DeltaRotatorTurret = AimAsRotator - TurretRotation;

		BigBarrel->Elevate(DeltaRotatorBarrel.Pitch);
		BigTurret->Rotate(DeltaRotatorTurret.Yaw);
	}
	else 
	{ 
		BarrelRotation = SmallBarrel->GetForwardVector().Rotation(); 
		TurretRotation = SmallTurret->GetForwardVector().Rotation();

		DeltaRotatorBarrel = AimAsRotator - BarrelRotation;
		DeltaRotatorTurret = AimAsRotator - TurretRotation;
		
		SmallBarrel->Elevate(DeltaRotatorBarrel.Pitch);
		SmallTurret->Rotate(DeltaRotatorTurret.Yaw);
	}
}