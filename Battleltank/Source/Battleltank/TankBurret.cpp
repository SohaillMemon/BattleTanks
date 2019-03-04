// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBurret.h"
#include "Engine/World.h "

void UTankBurret::Rotate(float RelativeSpeed)
{
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, 1);
	auto RotationChange = RelativeSpeed * MaxDegreesPerSecond* GetWorld()->DeltaTimeSeconds;
	auto Rotation = RelativeRotation.Yaw + RotationChange;
	SetRelativeRotation(FRotator(0,Rotation,0));
}


