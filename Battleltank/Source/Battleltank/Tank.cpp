// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"


// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void ATank::BeginPlay()
{
	Super::BeginPlay(); //needed for BP Begin Play to Run
	CurrentHealth = TotalHealth;
}


float ATank::GetHealthPercent()
{
	return (float)CurrentHealth / (float)TotalHealth;
}

EHealthBar ATank::GetHealthBarColor() const
{
	return HealthBarColor;
}


float ATank::TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser)
{
	int32 DamagePoint = FPlatformMath::RoundToInt(DamageAmount);
	int32 DamageToApply = FMath::Clamp(DamagePoint, 0, CurrentHealth);

	CurrentHealth -= DamageToApply;
	if (GetHealthPercent() <= 0.4)
	{
		HealthBarColor = EHealthBar::HealthLow;
	}

	else
	{
		HealthBarColor = EHealthBar::HealthHigh;
	}
	
	if(CurrentHealth <= 0)
		{
			OnDeath.Broadcast();
		}
	return DamageToApply;
}
