// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuWidget.h"

#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "Engine/World.h"
#include "MultiplayerLobby/MultiplayerLobbyGameInstance.h"

bool UMainMenuWidget::Initialize()
{
    bool bSuccess = Super::Initialize();
    if(PlayWithFriendsButton != nullptr) 
    {
        PlayWithFriendsButton->OnClicked.AddDynamic(this, &UMainMenuWidget::OnCreatePrivateLobby);
    }
    UE_LOG(LogTemp, Warning, TEXT("Initialize"));
    if(StartMatchmakingButton != nullptr) 
    {
        UE_LOG(LogTemp, Warning, TEXT("StartMatchmakingButton"));
        StartMatchmakingButton->OnClicked.AddDynamic(this, &UMainMenuWidget::UMainMenuWidget::OnStartMatchmaking);
    }

    return bSuccess;
}

void UMainMenuWidget::OnCreatePrivateLobby()
{
    UWorld* World = GetWorld();
    if(World == nullptr) return;
    
    UMultiplayerLobbyGameInstance* GameInstance = World->GetGameInstance<UMultiplayerLobbyGameInstance>();
    if(GameInstance == nullptr) return;

    MenuSwitch->SetActiveWidget(LoadingText);
    
    GameInstance->CreatePrivateLobby();
    
    RemoveFromViewport();
    
    UE_LOG(LogTemp, Warning, TEXT("Play With Friends clicked"));
}

void UMainMenuWidget::OnStartMatchmaking()
{
    UWorld* World = GetWorld();
    if(World == nullptr) return;
    
    UMultiplayerLobbyGameInstance* GameInstance = World->GetGameInstance<UMultiplayerLobbyGameInstance>();
    if(GameInstance == nullptr) return;

    MenuSwitch->SetActiveWidget(SearchingText);

    RemoveFromViewport();

    GameInstance->SearchLobby();

    UE_LOG(LogTemp, Warning, TEXT("Start Matchmaking clicked"));
}
