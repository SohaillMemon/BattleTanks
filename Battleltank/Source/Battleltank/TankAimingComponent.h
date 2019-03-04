// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

class UTankBarrel;
class UTankBurret; //forward Vector

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLELTANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();
	void SetBarrelReference(UTankBarrel*BarrelToSet);
	void SetBurretReference(UTankBurret*BurretToSet);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void AimAt(FVector HitLocation, float LaunchingSpeed);
	
private:
	UTankBarrel*Barrel = nullptr;
	UTankBurret*Burret = nullptr;
	void MoveBarrelTowards(FVector AimDirection);
};
