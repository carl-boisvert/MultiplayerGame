// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyPlayerNameWidget.h"

#include "Components/TextBlock.h"

void ULobbyPlayerNameWidget::SetPlayerName(FString NewPlayerName)
{
	PlayerNameText->SetText(FText::FromString(NewPlayerName));
}
