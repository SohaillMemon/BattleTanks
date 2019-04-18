// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "TankAimingComponent.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h "


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

	if (GetSightRayHitLocation(HitLocation))
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
		 GetLookVectorHitLocation(LookDirection, HitLocation);
	 }


	 return true;
	 
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
		 ECollisionChannel::ECC_Visibility)
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