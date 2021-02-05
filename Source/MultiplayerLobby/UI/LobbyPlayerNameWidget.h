// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LobbyPlayerNameWidget.generated.h"

/**
 * 
 */
UCLASS()
class MULTIPLAYERLOBBY_API ULobbyPlayerNameWidget : public UUserWidget
{
	GENERATED_BODY()


	public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* PlayerNameText;

	public:
	void SetPlayerName(FString NewPlayerName);
};
