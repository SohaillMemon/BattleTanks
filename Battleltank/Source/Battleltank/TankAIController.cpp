// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h "


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	
	auto PlayerPawn = GetPlayerTank();
	
	if (!PlayerPawn)
	{
		UE_LOG(LogTemp, Warning, TEXT("AI Tank cant find player tank"))
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AI Tank  Found Player: %s"), *(PlayerPawn->GetName()))
	}

}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	auto TankName = GetName();
	GetControlledTank()->AimAt(GetPlayerTank()->GetActorLocation());
}
ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const
{
	auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!PlayerPawn) { return nullptr; }
	return Cast<ATank>(PlayerPawn);
}
