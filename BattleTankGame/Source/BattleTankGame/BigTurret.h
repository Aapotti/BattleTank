// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "BigTurret.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANKGAME_API UBigTurret : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
    void Rotate(float RelativeSpeed);

private:
    UPROPERTY(EditAnywhere, Category = Setup)
        float MaxDegreesPerSecond = 10;
};
