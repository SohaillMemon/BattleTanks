// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "Templates/Casts.h "
#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

// forward declaration
class UTankBarrel; 
class UTankBurret;
class AProjectile;


UCLASS()
class BATTLELTANK_API ATank : public APawn
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "Firing")
	void Fire();

private:
	// Sets default values for this pawn's properties
	ATank();

	virtual void BeginPlay() override;

private:	
	
	// Called to bind functionality to input
	
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<AProjectile>ProjectileBlueprint;

	//TODO remove once it is moved to aiming component
	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float LaunchingSpeed = 4000.f;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float ReloadingSpeed = 3;


	UTankBarrel*Barrel = nullptr; //local barrel reference for spawning projectile //TODO remove


	double LastFireTime = 0;
};
