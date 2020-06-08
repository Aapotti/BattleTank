// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "TankBigBarrel.h"
#include "TankSmallBarrel.h"
#include "TankProjectile.h"
#include "TankSmallProjectile.h"
#include "Engine/World.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("AimingComponent"));
}


void ATank::SetBarrelReference(UTankBigBarrel* BigBarrelToSet, UTankSmallBarrel* SmallBarrelToSet)
{
	TankAimingComponent->SetBarrelReference(BigBarrelToSet, SmallBarrelToSet);
	BigBarrel = BigBarrelToSet;
	SmallBarrel = SmallBarrelToSet;
}


void ATank::SetTurretReference(UBigTurret* BigTurretToSet, USmallTurret* SmallTurretToSet)
{
	TankAimingComponent->SetTurretReference(BigTurretToSet, SmallTurretToSet);
}


// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ATank::AimAt(FVector AimingLocation)
{
	TankAimingComponent->Aim(AimingLocation, AimingWithBigGun, BigGunLaunchSpeed, SmallGunLaunchSpeed);
}

void ATank::ChangeCannon()
{
	if (AimingWithBigGun) 
	{ 
		AimingWithBigGun = false; 
		UE_LOG(LogTemp, Warning, TEXT("Small gun active"))
	}
	else 
	{ 
		AimingWithBigGun = true; 
		UE_LOG(LogTemp, Warning, TEXT("Big gun active"))
	}
}

void ATank::Fire()
{
	UE_LOG(LogTemp, Warning, TEXT("FIRE!"));

	if (!SmallBarrel || !BigBarrel) { return; }

	FActorSpawnParameters SpawnParams;
	FRotator SpawnRotation;
	FVector Spawnlocation; 


	if (AimingWithBigGun)
	{
		Spawnlocation = BigBarrel->GetSocketLocation(FName("Cannon"));
		SpawnRotation = BigBarrel->GetSocketRotation(FName("Cannon"));
		auto Projectile = GetWorld()->SpawnActor<ATankProjectile>(ProjectileBlueprint, Spawnlocation, SpawnRotation, SpawnParams);

		Projectile->FireProjectile(BigGunLaunchSpeed);
	}
	else
	{
		Spawnlocation = SmallBarrel->GetSocketLocation(FName("Small_Cannon"));
		SpawnRotation = SmallBarrel->GetSocketRotation(FName("Small_Cannon"));
		auto Projectile = GetWorld()->SpawnActor<ATankSmallProjectile>(SmallProjectileBlueprint, Spawnlocation, SpawnRotation, SpawnParams);

		Projectile->FireProjectile(BigGunLaunchSpeed);
	}
}