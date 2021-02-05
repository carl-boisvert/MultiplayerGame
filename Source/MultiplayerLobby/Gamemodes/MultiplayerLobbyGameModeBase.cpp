// Fill out your copyright notice in the Description page of Project Settings.


#include "MultiplayerLobbyGameModeBase.h"

#include "Kismet/GameplayStatics.h"
#include "MultiplayerLobby/MultiplayerLobbyGameInstance.h"
#include "MultiplayerLobby/PlayerStates/PlayerStateBase.h"


AMultiplayerLobbyGameModeBase::AMultiplayerLobbyGameModeBase()
{
    bUseSeamlessTravel = true;
}

//This is needed because for some reason OptionsString doesn't keep the params passed
//This is only called when the player client travel to the server, not on seamless travel
FString AMultiplayerLobbyGameModeBase::InitNewPlayer(APlayerController* NewPlayerController, const FUniqueNetIdRepl& UniqueId, const FString& Options, const FString& Portal)
{
    UE_LOG(LogTemp, Warning, TEXT("InitNewPlayer"))

    APlayerStateBase* PlayerStateBase = NewPlayerController->GetPlayerState<APlayerStateBase>();
    UMultiplayerLobbyGameInstance* GameInstance = GetGameInstance<UMultiplayerLobbyGameInstance>();

    FString playerId;
    if(GameInstance->HasJustLaunchedGame)
    {
        if (FParse::Value(FCommandLine::Get(), TEXT("playerId"), playerId)) { 
            PlayerStateBase->Id = playerId;
        }
        GameInstance->HasJustLaunchedGame = false;
    } else
    {
        playerId = UGameplayStatics::ParseOption(Options, TEXT("playerId"));
        if(playerId != "")
        {
            UE_LOG(LogTemp, Warning, TEXT("Player Id: %s"), *playerId);
            PlayerStateBase->Id = playerId;
        }
    }

    return Super::InitNewPlayer(NewPlayerController, UniqueId, Options, Portal);
}

//This is only called when the player client travel to the server, not on seamless travel
void AMultiplayerLobbyGameModeBase::PostLogin(APlayerController* NewPlayer)
{
    UE_LOG(LogTemp, Warning, TEXT("GameMode PostLogin"));
    UE_LOG(LogTemp, Warning, TEXT("Options: %s"), *OptionsString)

    Super::PostLogin(NewPlayer);
    NewPlayer->bShowMouseCursor = true; 
    NewPlayer->bEnableClickEvents = true; 
    NewPlayer->bEnableMouseOverEvents = true;

    APlayerStateBase* MenuPlayerState = NewPlayer->GetPlayerState<APlayerStateBase>();
    UMultiplayerLobbyGameInstance* GameInstance = GetGameInstance<UMultiplayerLobbyGameInstance>();
    if(GameInstance != nullptr)
    {
        UE_LOG(LogTemp, Warning, TEXT("Fetching player infos for player id: %s"), *MenuPlayerState->Id);
        PlayerControllersId.Add(MenuPlayerState->Id, NewPlayer);
        GameInstance->OnPlayerInfoFetchedDelegate.AddUObject(this, &AMultiplayerLobbyGameModeBase::OnPlayerInfoFetched);
        GameInstance->GetUserInfo(MenuPlayerState->Id);
    }
    
}

void AMultiplayerLobbyGameModeBase::OnPlayerInfoFetched(FString Id, FString PlayerName)
{
    APlayerController* PC = PlayerControllersId.FindAndRemoveChecked(Id);

    if(PC != nullptr)
    {
        APlayerStateBase* MenuPlayerState = PC->GetPlayerState<APlayerStateBase>();

        if(MenuPlayerState != nullptr)
        {
            UE_LOG(LogTemp, Warning, TEXT("Player Name Fetched: %s"), *PlayerName);
            MenuPlayerState->PlayerNameLocal = PlayerName;
            MenuPlayerState->OnRep_PlayerNameLocal();
        }
    }
}