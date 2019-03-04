// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBurret.generated.h"

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent), hidecategories= ("Collision"))
class BATTLELTANK_API UTankBurret : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:

	void Rotate(float RelativeSpeed);

private:

	UPROPERTY(EditAnywhere, Category = Setup)
	float MaxDegreesPerSecond = 25;

};
	
	

