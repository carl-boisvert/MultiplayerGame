// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuGamemode.h"

#include "MultiplayerLobby/PlayerStates/PlayerStateBase.h"

AMainMenuGamemode::AMainMenuGamemode()
{ 
    static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Pawns/BP_LobbyPawn"));
    if (PlayerPawnBPClass.Class != NULL)
    {
        DefaultPawnClass = PlayerPawnBPClass.Class;
    }

    PlayerStateClass = APlayerStateBase::StaticClass();
}
