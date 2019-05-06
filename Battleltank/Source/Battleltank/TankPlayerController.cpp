// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "TankAimingComponent.h"
#include "Tank.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h "

void ATankPlayerController::SetPawn(APawn * InPawn)
{
	Super::SetPawn(InPawn);
	if (InPawn)
	{
		auto PossessedTank = Cast<ATank>(InPawn);
		if (!ensure(PossessedTank)) { return; }

		// TODO subsribe our local method to tank's death event
		PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankPlayerController::OnPossessedTankDeath);
	}
}

void ATankPlayerController::OnPossessedTankDeath()
{
	StartSpectatingOnly();
}
void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponent)) { return; }
	FoundAimingComponent(AimingComponent);
}

	
void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrossHair();
	//aim towards the crosshair


}

void ATankPlayerController::AimTowardsCrossHair()
{
	if (!GetPawn()) { return; }
	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponent)) { return; }
	
	FVector HitLocation; // OUT Parameter
	
	bool bGotHitLocation = GetSightRayHitLocation(HitLocation);
	
	if (bGotHitLocation)
	{
		AimingComponent->AimAt(HitLocation);
	}

	 // TODO tell controlled taank to aim at the crosshair

}

// get world location of linetrace through crosshair, true if hits landscape
 bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const
{
	
	//find the crosshair position in pixel coordinates
	 int32 ViewPortSizeX, ViewPortSizeY;
	 GetViewportSize(ViewPortSizeX, ViewPortSizeY);

	 auto ScreenLocation = FVector2D(ViewPortSizeX *CrosshairXPoistion, ViewPortSizeY * CrosshairYPosition);

	 // de projects screen position of the cross hair to a world location
	 FVector LookDirection;
	 if (GetLookDirection(ScreenLocation, LookDirection))
	 {
		 return GetLookVectorHitLocation(LookDirection, HitLocation);
	 }


	 return false;
	 
}
 bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const
 {
	 FHitResult HitResult;
	 auto Startlocation = PlayerCameraManager->GetCameraLocation();
	 auto EndLocation = Startlocation + (LookDirection* LineTraceRange);

	 if (GetWorld()->LineTraceSingleByChannel(
		 HitResult,
		 Startlocation,
		 EndLocation,
		 ECollisionChannel::ECC_Camera)
		 )
	 {
		 HitLocation = HitResult.Location;
		 return true;
	 }
	 HitLocation = FVector(0);
	 return false;
	
 }

 bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const
 {
	
	 FVector CameraWorldLocation;// to be discarded

	return DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, CameraWorldLocation, LookDirection);
	

 }