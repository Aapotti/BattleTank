// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"

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