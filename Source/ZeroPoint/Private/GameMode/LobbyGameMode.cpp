// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/LobbyGameMode.h"

#include "Engine/World.h"

ALobbyGameMode::ALobbyGameMode()
{
	bUseSeamlessTravel = true;
}

void ALobbyGameMode::OnPostLogin(AController* NewPlayer)
{
	Super::OnPostLogin(NewPlayer);
	
	int32 CurrentPlayers = GetNumPlayers();
	
	if (CurrentPlayers >= 2)
	{
		UWorld* World = GetWorld();
		if (World)
		{
			World->ServerTravel(TEXT("/Game/Maps/ZeroPointMap"));
		}
	}
}
