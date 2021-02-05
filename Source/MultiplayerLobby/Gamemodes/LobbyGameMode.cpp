// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyGameMode.h"

#include "MultiplayerLobby/PlayerStates/PlayerStateBase.h"

ALobbyGameMode::ALobbyGameMode()
{
    static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Pawns/BP_LobbyPawn"));
    UE_LOG(LogTemp,Warning, TEXT("ALobbyGameMode Construction"))
    if (PlayerPawnBPClass.Class != NULL)
    {
        DefaultPawnClass = PlayerPawnBPClass.Class;
    }

    PlayerStateClass = APlayerStateBase::StaticClass();
}
