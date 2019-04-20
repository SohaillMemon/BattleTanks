// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankBurret.h"
#include "Components/ActorComponent.h"
#include "Kismet/GameplayStatics.h "
#include "Projectile.h"




UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true; //TODO should these really tick?


	//....
}

void UTankAimingComponent::BeginPlay()
{

	LastFireTime = FPlatformTime::Seconds();
	// ...

}

// Sets default values for this component's properties
void UTankAimingComponent::Initialize(UTankBarrel*BarrelToSet, UTankBurret*BurretToSet)
{

	Barrel = BarrelToSet;
	Burret = BurretToSet;
}

void UTankAimingComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	if (RoundLeft <= 0)
	{
		FiringState = EFiringState::OutOfAmmo;
	}

    else if ((FPlatformTime::Seconds() - LastFireTime) < ReloadingSpeed)
	{
		FiringState = EFiringState::Reloading;
	}
	else if(IsBarrelMoving())
	{

		FiringState = EFiringState::Aiming;
		
	}
	else
	{
		FiringState = EFiringState::Locked;
	}
}

EFiringState UTankAimingComponent::GetFiringState() const
{
	return FiringState;
}

int UTankAimingComponent::GetRoundsLeft() const
{
	return RoundLeft;
}

bool UTankAimingComponent::IsBarrelMoving()
{
	if (!ensure(Barrel)) { return false; }
	auto BarrelForward = Barrel->GetForwardVector();
	return !BarrelForward.Equals(AimDirection, 0.01); //vectors are not equal

}

// Called when the game starts




void UTankAimingComponent::AimAt(FVector HitLocation)
{
	if (!ensure(Barrel)) { return; }
	FVector OutLaunchVelocity(0);
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));

	//calculate outlaunchvelocity

	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity
	(
		this,
		OutLaunchVelocity,
		StartLocation,
		HitLocation,
		LaunchingSpeed,
		false,
		0,
		0,
		ESuggestProjVelocityTraceOption::DoNotTrace //parameter must be present to prevent bug
	);
	
	if (bHaveAimSolution)
	{
		AimDirection = OutLaunchVelocity.GetSafeNormal();
		MoveBarrelTowards(AimDirection);
		
	}
	
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	
	//work out difference between current barrel rotation and aimdirection
	if (!ensure(Barrel) || !ensure(Burret)) { return; }
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimRotator = AimDirection.Rotation();
	auto DeltaRotator = AimRotator - BarrelRotator;
	
	Barrel->Elevate(DeltaRotator.Pitch);

	//always yaw the shortest path
	Burret->Rotate(DeltaRotator.GetNormalized().Yaw);

}

void UTankAimingComponent::Fire()
{
	
	

	if (FiringState == EFiringState::Locked || FiringState == EFiringState::Aiming)
	{
		if (!ensure(Barrel)) { return; }
		if (!ensure(ProjectileBlueprint)) { return; }
		// spawn fire projectile at socket location of barrel
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(
			ProjectileBlueprint,
			Barrel->GetSocketLocation(FName("Projectile")),
			Barrel->GetSocketRotation(FName("Projectile"))
			);

		Projectile->LaunchProjectile(LaunchingSpeed);
		LastFireTime = FPlatformTime::Seconds();
		RoundLeft--;
		
	}

}

