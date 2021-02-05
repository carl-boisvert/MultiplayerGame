// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerStateBase.h"

#include "Engine/DemoNetDriver.h"
#include "MultiplayerLobby/Pawns/LobbyPawn.h"

void APlayerStateBase::SeamlessTravelTo(APlayerState* NewPlayerState)
{
	Super::SeamlessTravelTo(NewPlayerState);

	APlayerStateBase* MenuPlayerState = Cast<APlayerStateBase>(NewPlayerState);

	UE_LOG(LogTemp, Warning, TEXT("SeamlessTravelTo"));
    
	if(MenuPlayerState != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("SeamlessTravelTo Worked For %s"), *this->PlayerNameLocal);
		MenuPlayerState->Id = this->Id;
		MenuPlayerState->PlayerNameLocal = this->PlayerNameLocal;
	}
}

void APlayerStateBase::CopyProperties(APlayerState* PlayerState)
{
	Super::CopyProperties(PlayerState);
    
	APlayerStateBase* MenuPlayerState = Cast<APlayerStateBase>(PlayerState);

	UE_LOG(LogTemp, Warning, TEXT("CopyProperties"));
    
	if(MenuPlayerState != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("CopyProperties Worked For %s"), *this->PlayerNameLocal);
		MenuPlayerState->Id = this->Id;
		MenuPlayerState->PlayerNameLocal = this->PlayerNameLocal;
	}
}

void APlayerStateBase::OverrideWith(APlayerState* PlayerState)
{
	Super::OverrideWith(PlayerState);

	APlayerStateBase* MenuPlayerState = Cast<APlayerStateBase>(PlayerState);

	UE_LOG(LogTemp, Warning, TEXT("OverrideWith"));
    
	if(MenuPlayerState != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("OverrideWith Worked For %s"), *MenuPlayerState->PlayerNameLocal);
		this->Id = MenuPlayerState->Id;
		this->PlayerNameLocal = MenuPlayerState->PlayerNameLocal;
	}
}

// This can't use ALobbyPawn directly
void APlayerStateBase::OnRep_PlayerNameLocal()
{
	APawn* Pawn = GetPawn();
	if(Pawn != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Pawn: %s"), GetPawn());
		ALobbyPawn* PlayerPawn = GetPawn<ALobbyPawn>();
		if(PlayerPawn)
		{
			PlayerPawn->OnPlayerNameLocalChanged(PlayerNameLocal);
		}
	} else
	{
		UE_LOG(LogTemp, Warning, TEXT("Pawn is null"), GetPawn());
	}
}

void APlayerStateBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(APlayerStateBase, Id);
	DOREPLIFETIME(APlayerStateBase, PlayerNameLocal);
}