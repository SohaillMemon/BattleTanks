// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "TankAimingComponent.h"
#include "TankBurret.h"
#include "TankBarrel.h"
#include "Projectile.h"
#include "TankMovementComponent.h"




// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}





void ATank::AimAt(FVector HitLocation)
{
	TankAimingComponent->AimAt(HitLocation, LaunchingSpeed);
	
}


void ATank::Fire()
{
	bool isReloded = (FPlatformTime::Seconds() - LastFireTime) > ReloadingSpeed;

	if (Barrel && isReloded)
	{

		// spawn fire projectile at socket location of barrel
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(
			ProjectileBlueprint,
			Barrel->GetSocketLocation(FName("Projectile")),
			Barrel->GetSocketRotation(FName("Projectile"))
			);

		Projectile->LaunchProjectile(LaunchingSpeed);
		LastFireTime = FPlatformTime::Seconds();
	}
 
}