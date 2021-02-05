// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "MultiplayerLobbyGameModeBase.h"
#include "GameFramework/PlayerController.h"

#include "LobbyGameMode.generated.h"

/**
 * 
 */
UCLASS()
class MULTIPLAYERLOBBY_API ALobbyGameMode : public AMultiplayerLobbyGameModeBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Spawn")
	TArray<AActor*> SpawnPoints;

public:
	ALobbyGameMode();
};
