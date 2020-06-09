// Fill out your copyright notice in the Description page of Project Settings.


#include "TankSmallBarrel.h"
#include "Math/UnrealMathUtility.h"

void UTankSmallBarrel::Elevate(float RelativeSpeed)
{
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, 1);

	auto ElevationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto Elevation = RelativeRotation.Pitch + ElevationChange;

	Elevation = FMath::Clamp(Elevation, MinElevationDegrees, MaxElevationDegrees);

	SetRelativeRotation(FRotator(Elevation, 0, 0));
}