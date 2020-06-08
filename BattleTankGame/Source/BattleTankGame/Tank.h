// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "TankAimingComponent.h"
#include "Tank.generated.h"

class UTankBigBarrel;
class UTankSmallBarrel;

class UBigTurret;
class USmallTurret;

class ATankProjectile;
class ATankSmallProjectile;

UCLASS()
class BATTLETANKGAME_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UTankAimingComponent* TankAimingComponent = nullptr;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void AimAt(FVector AimingLocation);

	UFUNCTION(BlueprintCallable, Category = Setup)
		void SetBarrelReference(UTankBigBarrel* BigBarrelToSet, UTankSmallBarrel* SmallBarrelToSet);

	UFUNCTION(BlueprintCallable, Category = Setup)
		void SetTurretReference(UBigTurret* BigTurretToSet, USmallTurret* SmallTurretToSet);

	UFUNCTION(BlueprintCallable, Category = Guns)
		void ChangeCannon();

	UFUNCTION(BlueprintCallable, Category = Guns)
		void Fire();

	bool AimingWithBigGun = true;

	UPROPERTY(EditAnywhere, Category = Firing)
		float BigGunLaunchSpeed = 100000.f;

	UPROPERTY(EditAnywhere, Category = Firing)
		float SmallGunLaunchSpeed = 70000.f;

	UPROPERTY(EditAnywhere, Category = Firing)
		TSubclassOf<ATankProjectile> ProjectileBlueprint;

	UPROPERTY(EditAnywhere, Category = Firing)
		TSubclassOf<ATankSmallProjectile> SmallProjectileBlueprint;

	UTankBigBarrel* BigBarrel = nullptr;
	UTankSmallBarrel* SmallBarrel = nullptr;
};
