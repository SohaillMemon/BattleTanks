// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankBurret.h"
#include "Components/ActorComponent.h"
#include "Kismet/GameplayStatics.h "

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true; //TODO should these really tick?

	// ...
}


void  UTankAimingComponent::SetBarrelReference(UTankBarrel*BarrelToSet)
{
	Barrel = BarrelToSet;
}

void UTankAimingComponent::SetBurretReference(UTankBurret * BurretToSet)
{
	Burret = BurretToSet;
}


// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchingSpeed)
{
	if (!Barrel) { return; }
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
		auto AimDirection = OutLaunchVelocity.GetSafeNormal();
		MoveBarrelTowards(AimDirection);
		auto Time = GetWorld()->GetTimeSeconds();
		UE_LOG(LogTemp, Warning, TEXT("%f:aim solution found"), Time);
		//get location of barrel
		//movethe barrel to cursor location
	}
	else
	{
		auto Time = GetWorld()->GetTimeSeconds();
		UE_LOG(LogTemp, Warning, TEXT("%f: no aim solution found"), Time);
	}

}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	//work out difference between current barrel rotation and aimdirection
	
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimRotator = AimDirection.Rotation();
	auto DeltaRotator = AimRotator - BarrelRotator;
	
	Barrel->Elevate(DeltaRotator.Pitch);
	Burret->Rotate(DeltaRotator.GetNormalized().Yaw);
}

