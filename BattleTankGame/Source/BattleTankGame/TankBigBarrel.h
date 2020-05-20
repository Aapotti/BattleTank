// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBigBarrel.generated.h"

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANKGAME_API UTankBigBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	void Elevate(float DegreesPerSec);

private:
	UPROPERTY(EditAnywhere, Category = Setup)
		float MaxDegreesPerSecond = 10;
	UPROPERTY(EditAnywhere, Category = Setup)
		float MaxElevationDegrees = 5;
	UPROPERTY(EditAnywhere, Category = Setup)
		float MinElevationDegrees = -10;

};