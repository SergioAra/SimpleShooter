// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ShooterPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLESHOOTER_API AShooterPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AShooterPlayerController();
	virtual void GameHasEnded(AActor* EndGameFocus, bool bIsWinner) override;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> LoseScreen;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> WinScreen;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> HUD;

	UPROPERTY()
	UUserWidget* HUDWidget;
	
	UPROPERTY(EditAnywhere)
	float RestartDelay;

	FTimerHandle RestartTimer;
	
};
