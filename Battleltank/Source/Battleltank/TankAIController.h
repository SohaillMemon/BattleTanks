// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

/**
 * 
 */

//forward declaration

UCLASS()
class BATTLELTANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()
protected:
	//how close the ai tank can get
	UPROPERTY(EditDefaultsOnly, category = "Setup") 
	float AcceptanceRadius = 8000.;
private:

	virtual void BeginPlay() override;
	
	virtual void Tick(float DeltaTime) override;

	virtual void SetPawn(APawn* InPawn) override;

	UFUNCTION()
	void OnPossessedTankDeath();
	
};
