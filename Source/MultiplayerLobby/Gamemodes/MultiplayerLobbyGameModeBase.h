// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MultiplayerLobbyGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class MULTIPLAYERLOBBY_API AMultiplayerLobbyGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

private:
	UPROPERTY()
	TMap<FString, APlayerController*> PlayerControllersId;
	
public:
	AMultiplayerLobbyGameModeBase();
	void OnPlayerInfoFetched(FString Id, FString PlayerName);
	virtual void PostLogin(APlayerController* NewPlayer) override;
	
protected:
	virtual FString InitNewPlayer(APlayerController* NewPlayerController, const FUniqueNetIdRepl& UniqueId, const FString& Options, const FString& Portal) override;

	
};
