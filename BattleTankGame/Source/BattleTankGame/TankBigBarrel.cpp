// Fill out your copyright notice in the Description page of Project Settings.


#include "TankBigBarrel.h"
#include "Math/UnrealMathUtility.h"

void UTankBigBarrel::Elevate(float RelativeSpeed)
{
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, 1);

	auto ElevationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto Elevation = RelativeRotation.Pitch + ElevationChange;

	Elevation = FMath::Clamp(Elevation, MinElevationDegrees, MaxElevationDegrees);

	SetRelativeRotation(FRotator(Elevation, 0, 0));
}