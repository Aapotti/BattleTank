// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAimingComponent.h"
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

	if (UGameplayStatics::SuggestProjectileVelocity(
		this,
		OutLaunchVelocity,
		FiringLocation,
		AimingLocation,
		LaunchSpeed,
		false,
		0,
		0,
		ESuggestProjVelocityTraceOption::DoNotTrace
	))
	{
		auto AimDirection = OutLaunchVelocity.GetSafeNormal();
		UE_LOG(LogTemp, Warning, TEXT("Aiming at %s"), *AimDirection.ToString());
	}
}

void UTankAimingComponent::Fire()
{

}