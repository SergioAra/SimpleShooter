// Fill out your copyright notice in the Description page of Project Settings.


#include "KillAllGameMode.h"

#include "EngineUtils.h"
#include "ShooterAIController.h"

void AKillAllGameMode::PawnKilled(APawn* PawnKilled)
{
	Super::PawnKilled(PawnKilled);

	APlayerController* PlayerController = Cast<APlayerController>(PawnKilled->GetController());
	if(PlayerController)
	{
		EndGame(false);
	}
	for(AShooterAIController* Controller : TActorRange<AShooterAIController>(GetWorld()))
	{
		if(!Controller->IsDead())
		{
			return;
		}
	}
	EndGame(true);
}

void AKillAllGameMode::EndGame(bool bIsPlayerWinner)
{
	
	for(AController* Controller : TActorRange<AController>(GetWorld()))
	{
		bool bIsWinner = Controller->IsPlayerController() == bIsPlayerWinner;
		Controller->GameHasEnded(Controller->GetPawn(), bIsWinner);
	}
}
