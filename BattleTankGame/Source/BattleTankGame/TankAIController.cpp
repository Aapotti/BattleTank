// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAIController.h"
#include "Engine/World.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	auto PlayerTank = GetPlayerTank();

	if (!PlayerTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("AIContrtoller did not find the player tank"))
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AIContrtoller has found the player tank %s"), *(PlayerTank->GetName()))
	}
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (GetPlayerTank())
	{
		AimAtPlayer();

		GetAITank()->Fire();
	}
}

ATank* ATankAIController::GetAITank() const
{
	return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const
{
	auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!PlayerPawn) {return nullptr;}
	return Cast<ATank>(PlayerPawn);
}

void ATankAIController::AimAtPlayer()
{
	auto PlayerPawnLocation = GetPlayerTank()->GetActorLocation();

	GetAITank()->AimAt(PlayerPawnLocation);
}