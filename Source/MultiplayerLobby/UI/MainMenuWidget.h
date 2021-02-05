// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Interfaces/OnlineSessionInterface.h"

#include "MainMenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class MULTIPLAYERLOBBY_API UMainMenuWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UButton* PlayWithFriendsButton;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UButton* StartMatchmakingButton;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UWidgetSwitcher* MenuSwitch;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UWidget* MainMenuScreen;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UWidget* SearchingText;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UWidget* LoadingText;

public:
	virtual bool Initialize() override;
	UFUNCTION()
    void OnCreatePrivateLobby();
	UFUNCTION()
    void OnStartMatchmaking();
};
