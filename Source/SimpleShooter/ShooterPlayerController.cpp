// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterPlayerController.h"

#include "Blueprint/UserWidget.h"

AShooterPlayerController::AShooterPlayerController():
	RestartDelay(5.f)
{
}

void AShooterPlayerController::GameHasEnded(AActor* EndGameFocus, bool bIsWinner)
{
	Super::GameHasEnded(EndGameFocus, bIsWinner);

	if(HUDWidget)
	{
		HUDWidget->RemoveFromViewport();
	}

	if(bIsWinner)
	{
		UUserWidget* WinScreenWidget = CreateWidget(this, WinScreen);
		if(WinScreenWidget)
		{
			WinScreenWidget->AddToViewport();
		}
	}
	else
	{
		UUserWidget* LoseScreenWidget = CreateWidget(this, LoseScreen);
		if(LoseScreenWidget)
		{
			LoseScreenWidget->AddToViewport();
		}
	}
	GetWorldTimerManager().SetTimer(RestartTimer, this, &APlayerController::RestartLevel, RestartDelay);
}

void AShooterPlayerController::BeginPlay()
{
	Super::BeginPlay();

	HUDWidget = CreateWidget(this, HUD);
	if(HUDWidget)
	{
		HUDWidget->AddToViewport();
	}
}
