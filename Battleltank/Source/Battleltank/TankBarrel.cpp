// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"
#include "Engine/World.h "


void UTankBarrel::Elevate(float Speed)
{
	Speed = FMath::Clamp<float>(Speed, -1, 1);
	auto ElevationChange = Speed * MaxDegreesPerSecond* GetWorld()->DeltaTimeSeconds;
	auto RawNewElevation = RelativeRotation.Pitch + ElevationChange;
	auto Elevation = FMath::Clamp<float>(RawNewElevation, MinElevationDegrees, MaxElevationDegrees);
	SetRelativeRotation(FRotator(Elevation, 0, 0));


	//move the barrel the right amount this frame
	//give a max elevation speed and frame rate
}

