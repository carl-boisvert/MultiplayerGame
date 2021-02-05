// Copyright Epic Games, Inc. All Rights Reserved.

#include "MultiplayerLobbyGameMode.h"
#include "MultiplayerLobbyCharacter.h"
#include "UObject/ConstructorHelpers.h"

AMultiplayerLobbyGameMode::AMultiplayerLobbyGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
