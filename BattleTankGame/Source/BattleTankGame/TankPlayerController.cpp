// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPlayerController.h"
#include "DrawDebugHelpers.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	auto ControlledTank = GetControlledTank();

	if (!ControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerContrtoller does not have a pawn"))
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerContrtoller has %s"), *(ControlledTank->GetName()))
	}
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
}

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair() 
{
	if (!GetControlledTank()) { return; }

	FVector HitLocation;
	if (GetSightRayHitLocation(HitLocation)) 
	{
		GetControlledTank()->AimAt(HitLocation);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Line Trace Failed :("));
	}
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& OutHitLocation) const 
{
	// Find crosshair position in pixel coordinates
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	auto CrosshairLocation = FVector2D(ViewportSizeX * CrosshairXLocation, ViewportSizeY * CrosshairYLocation);

	// "De-project" the screen position of the crosshair to a world direction
	FVector CameraWorldLocation;
	FVector WorldDirection;
	if (DeprojectScreenPositionToWorld(CrosshairLocation.X, CrosshairLocation.Y, CameraWorldLocation, WorldDirection))
	{
		// Line-trace along that look direction and see what we hit
		FHitResult ImpactPoint;

		FVector StartingPoint = PlayerCameraManager->GetCameraLocation();
		FVector EndPoint = (StartingPoint + (WorldDirection * LineTraceRange));

		// This would visualize the line trace:
		// DrawDebugLine(GetWorld(), StartingPoint, EndPoint, FColor::Blue, false, 1, 0, 1);

		bool IsHit = GetWorld()->LineTraceSingleByChannel(ImpactPoint, StartingPoint, EndPoint, ECC_Visibility);

		if (IsHit)
		{
			OutHitLocation = ImpactPoint.Location;
			return true;
		}
	}
	return false; // Line Trace Didn't Succeed
}