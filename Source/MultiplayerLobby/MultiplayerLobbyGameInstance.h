// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "OnlineSubsystem.h"
#include "OnlineSessionSettings.h"
#include "Interfaces/IHttpRequest.h"
#include "Interfaces/OnlineSessionInterface.h"

#include "MultiplayerLobbyGameInstance.generated.h"

DECLARE_MULTICAST_DELEGATE_TwoParams(FPlayerInfoFetchedDelegate, FString, FString)

/**
 * 
 */
UCLASS()
class MULTIPLAYERLOBBY_API UMultiplayerLobbyGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	FPlayerInfoFetchedDelegate OnPlayerInfoFetchedDelegate;
	bool HasJustLaunchedGame = true;
	
private:
	class FHttpModule* Http;
	IOnlineIdentityPtr IdentityInterface;
	class IOnlineSession* OnlineSessionInterface;
	TSharedPtr<FOnlineSessionSearch> OnlineSessionSearch;
	
public:
	void CreatePrivateLobby();
	void SearchLobby();
	void GetUserInfo(FString id);
    void CreatePrivateSessionComplete(FName SessionName, bool bWasSuccessful);
	void OnFindSessionsComplete(bool bWasSuccessful);
	void OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result);
	void OnGetUserInfoResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully);
	
private:
	bool InitOnlineSessionInterface();
	
};
