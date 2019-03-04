// Fill out your copyright notice in the Description page of Project Settings.

#pragma once



#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

// forward declaration
class UTankBarrel; 
class UTankAimingComponent;
class UTankBurret;

UCLASS()
class BATTLELTANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	void AimAt(FVector HitLocation);
	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetBarrelReference(UTankBarrel*BarrelToSet);

	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetBurretReference(UTankBurret*BurretToSet);

private:
	// Sets default values for this pawn's properties
	ATank();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UTankAimingComponent*TankAimingComponent = nullptr;

private:	
	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, Category = Firing)
	float LaunchingSpeed = 100000.f;
	
};
