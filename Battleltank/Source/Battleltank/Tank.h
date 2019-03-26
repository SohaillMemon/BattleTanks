// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "Templates/Casts.h "
#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

// forward declaration
class UTankBarrel; 
class UTankAimingComponent;
class UTankBurret;
class AProjectile;
class UTankMovementComponent;

UCLASS()
class BATTLELTANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	void AimAt(FVector HitLocation);


	UFUNCTION(BlueprintCallable, Category = "Firing")
	void Fire();

private:
	// Sets default values for this pawn's properties
	ATank();


protected:


	UPROPERTY(BlueprintReadOnly)
	UTankAimingComponent*TankAimingComponent = nullptr;

	UPROPERTY(BlueprintReadOnly)
	UTankMovementComponent* TankMovementComponent = nullptr;


private:	
	
	// Called to bind functionality to input
	
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<AProjectile>ProjectileBlueprint;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float LaunchingSpeed = 4000.f;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float ReloadingSpeed = 3;


	UTankBarrel*Barrel = nullptr; //local barrel reference for spawning projectile //TODO remove


	double LastFireTime = 0;
};
