// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

/**
 * 
 */

//forward delaration
class ATank;

UCLASS()
class BATTLELTANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

private:

	ATank* GetControlledTank() const;

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	void AimTowardsCrossHair();

	bool GetSightRayHitLocation(FVector& HitLocation) const;
	
	
	UPROPERTY(EditAnywhere)
	float CrosshairXPoistion = 0.5;

	UPROPERTY(EditAnywhere)
	float CrosshairYPosition = 0.3333;

	bool GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const;

	UPROPERTY(EditAnywhere)
	float LineTraceRange = 100000;

	bool GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const;

};