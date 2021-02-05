// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "PlayerStateBase.generated.h"

/**
 * 
 */
UCLASS()
class MULTIPLAYERLOBBY_API APlayerStateBase : public APlayerState
{
	GENERATED_BODY()

public:
	UPROPERTY(Replicated)
	FString Id;
	UPROPERTY(Replicated, ReplicatedUsing=OnRep_PlayerNameLocal)
	FString PlayerNameLocal;

public:
	virtual void SeamlessTravelTo(APlayerState* NewPlayerState) override;
	UFUNCTION()
    virtual void OnRep_PlayerNameLocal();

protected:
	virtual void CopyProperties(APlayerState* PlayerState) override;
	virtual void OverrideWith(APlayerState* PlayerState) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
};
