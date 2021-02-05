// Fill out your copyright notice in the Description page of Project Settings.

#include "MultiplayerLobbyGameInstance.h"

#include "HttpModule.h"
#include "Interfaces/IHttpRequest.h"
#include "Interfaces/IHttpResponse.h"
#include "OnlineSubsystem.h"
#include "Interfaces/OnlineIdentityInterface.h"
#include "OnlineSessionSettings.h"
#include "PlayerStates/PlayerStateBase.h"

bool UMultiplayerLobbyGameInstance::InitOnlineSessionInterface()
{
    IOnlineSubsystem* Oss = IOnlineSubsystem::Get("NULL");
    if(Oss == nullptr) return false;

    IdentityInterface = Oss->GetIdentityInterface();
    if(IdentityInterface == nullptr) return false;
    
    //Check if there's a session
    const IOnlineSessionPtr SessionInterface = Oss->GetSessionInterface();
    if(SessionInterface == nullptr)  return false;
    
    OnlineSessionInterface = SessionInterface.Get();
    if(OnlineSessionInterface == nullptr)  return false;

    return true;
}

void UMultiplayerLobbyGameInstance::SearchLobby()
{
    bool bIsInitialized = InitOnlineSessionInterface();

    if(!bIsInitialized)
    {
        UE_LOG(LogTemp, Error, TEXT("Couldn't initialize online subsytem"));
        return;
    }
    
    OnlineSessionInterface->OnFindSessionsCompleteDelegates.AddUObject(this, &UMultiplayerLobbyGameInstance::OnFindSessionsComplete);

    OnlineSessionSearch = MakeShared<FOnlineSessionSearch>();
    OnlineSessionInterface->FindSessions(*IdentityInterface->GetUniquePlayerId(0).Get(), OnlineSessionSearch.ToSharedRef());
}

void UMultiplayerLobbyGameInstance::GetUserInfo(FString id)
{
    Http = &FHttpModule::Get();

    TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = Http->CreateRequest();
    Request->OnProcessRequestComplete().BindUObject(this, &UMultiplayerLobbyGameInstance::OnGetUserInfoResponseReceived);
    //This is the url on which to process the request
    Request->SetURL("http://localhost:8080/users/"+id);
    Request->SetVerb("GET");
    Request->SetHeader(TEXT("User-Agent"), "X-UnrealEngine-Agent");
    Request->SetHeader("Content-Type", TEXT("application/json"));
    Request->ProcessRequest();
}

void UMultiplayerLobbyGameInstance::CreatePrivateLobby()
{
    bool bIsInitialized = InitOnlineSessionInterface();
    
    if(!bIsInitialized)
    {
        UE_LOG(LogTemp, Error, TEXT("Couldn't initialize online subsytem"));
        return;
    }
    
    OnlineSessionInterface->OnCreateSessionCompleteDelegates.AddUObject(this, &UMultiplayerLobbyGameInstance::CreatePrivateSessionComplete);
    
    FOnlineSessionSettings FoSettings;
    FoSettings.bAllowInvites = true;
    FoSettings.bIsDedicated = false;
    FoSettings.bShouldAdvertise = true;
    FoSettings.bUsesPresence = true;
    FoSettings.NumPrivateConnections = 4;
    FoSettings.NumPublicConnections = 4;
    FoSettings.bAllowJoinInProgress = true;
    FoSettings.bAllowJoinViaPresence = true;
    FoSettings.bAllowJoinViaPresenceFriendsOnly = true; 
    

    const FName SessionName = FName("Rosie's session");
    FNamedOnlineSession* ExistingSession = OnlineSessionInterface->GetNamedSession(SessionName);
    if(ExistingSession != nullptr)
    {
        OnlineSessionInterface->DestroySession(SessionName);
    }
    
    FOnlineSessionSetting SessionNameSetting;
    SessionNameSetting.AdvertisementType = EOnlineDataAdvertisementType::ViaOnlineService;
    SessionNameSetting.Data = SessionName.ToString();
    FoSettings.Settings.Add(FName("SESSION_NAME"), SessionNameSetting);
    
    OnlineSessionInterface->CreateSession(0, SessionName, FoSettings);
}

void UMultiplayerLobbyGameInstance::CreatePrivateSessionComplete(FName SessionName, bool bWasSuccessful)
{
    UE_LOG(LogTemp, Warning, TEXT("Session %s created"), *SessionName.ToString());
    UWorld* World = GetWorld();
    
    World->ServerTravel("/Game/Maps/Lobby?listen");
}

void UMultiplayerLobbyGameInstance::OnFindSessionsComplete(bool bWasSuccessful)
{
    UE_LOG(LogTemp, Warning, TEXT("Session found in matchmaking: %i"), bWasSuccessful);

    if(bWasSuccessful && OnlineSessionSearch.IsValid()){
        TArray<FOnlineSessionSearchResult> Results = OnlineSessionSearch->SearchResults;
        if(Results.Num() > 0)
        {
            FOnlineSessionSearchResult SearchResult = Results[0];

            FName SessionName = FName(SearchResult.Session.SessionSettings.Settings.FindRef("SESSION_NAME").Data.ToString());

            OnlineSessionInterface->OnJoinSessionCompleteDelegates.AddUObject(this, &UMultiplayerLobbyGameInstance::OnJoinSessionComplete);
            OnlineSessionInterface->JoinSession(0, SessionName, SearchResult); 
        } else
        {
            UE_LOG(LogTemp, Error, TEXT("Couldn't find any session"))
        }
    }
}

void UMultiplayerLobbyGameInstance::OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result)
{   
    if(Result == EOnJoinSessionCompleteResult::Success)
    {
        FString Address;
        OnlineSessionInterface->GetResolvedConnectString(SessionName, Address);

        APlayerController* PC = GetFirstLocalPlayerController();
        
        if(PC != nullptr)
        {
            APlayerStateBase* MenuPlayerState = PC->GetPlayerState<APlayerStateBase>();
            if(MenuPlayerState != nullptr)
            {
                FString FullAddress = FString::Printf(TEXT("%s?playerId=%s"), *Address, *MenuPlayerState->Id);
                PC->ClientTravel(FullAddress, ETravelType::TRAVEL_Relative);
            }
        }
    }
    
}

void UMultiplayerLobbyGameInstance::OnGetUserInfoResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully)
{
    UE_LOG(LogTemp, Warning, TEXT("Server response"));

    TSharedPtr<FJsonObject> JsonObject;

    //Create a reader pointer to read the json data
    TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());

    //Deserialize the json data given Reader and the actual object to deserialize
    if (FJsonSerializer::Deserialize(Reader, JsonObject))
    {
        //Get the value of the json object by field name
        TSharedPtr<FJsonObject> user = JsonObject->GetObjectField("user");
        const FString Id = user->GetStringField("id");
        const FString PlayerName = user->GetStringField("playerName");
        OnPlayerInfoFetchedDelegate.Broadcast(Id, PlayerName);
    }
}
