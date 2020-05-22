// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

class UTankBigBarrel;
class UTankSmallBarrel;

class UBigTurret;
class USmallTurret;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANKGAME_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

	void SetBarrelReference(UTankBigBarrel* BigBarrelToSet, UTankSmallBarrel* SmallBarrelToSet);

	void SetTurretReference(UBigTurret* BigTurretToSet, USmallTurret* SmallTurretToSet);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	UTankBigBarrel* BigBarrel = nullptr;
	UTankSmallBarrel* SmallBarrel = nullptr;

	UBigTurret* BigTurret = nullptr;
	USmallTurret* SmallTurret = nullptr;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void Aim(FVector AimingLocation, bool AimingWithBigGun, float BigGunLaunchSpeed,  float SmallGunLaunchSpeed);

	void MoveBarrelAndTurret(FVector AimDirection, bool AimingWithBigGun);
	void Fire();
};
