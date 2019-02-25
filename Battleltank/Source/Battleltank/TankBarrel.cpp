// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"


void UTankBarrel::Elevate(float DegreesPersecond)
{
	UE_LOG(LogTemp, Warning, TEXT("Elevate-barrel with speed %f"), DegreesPersecond);
	//move the barrel the right amount this frame
	//give a max elevation speed and frame rate
}

