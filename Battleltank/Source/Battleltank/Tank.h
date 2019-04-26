// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "Templates/Casts.h "
#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"



UENUM()
enum class EHealthBar : uint8
{
	HealthHigh,
	HealthLow
};

// forward declaration
class UTankBarrel; 
class UTankBurret;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTankDelegate);

UCLASS()
class BATTLELTANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	//called by the engine when actor damage is dealt
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser) override;

	UFUNCTION(BlueprintPure, Category = "Health")
	float GetHealthPercent();

	EHealthBar GetHealthBarColor() const;

	FTankDelegate OnDeath;

private:
	// Sets default values for this pawn's properties
	ATank();

	virtual void BeginPlay() override;


	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	int32 TotalHealth = 100;
	
	UPROPERTY(VisibleAnywhere, Category = "Health")
	int32 CurrentHealth; 

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction);

protected:
	UPROPERTY(BlueprintReadOnly, Category = "State")
	EHealthBar HealthBarColor = EHealthBar::HealthHigh;
};
