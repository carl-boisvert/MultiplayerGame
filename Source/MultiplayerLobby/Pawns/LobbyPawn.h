// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "LobbyPawn.generated.h"

UCLASS()
class MULTIPLAYERLOBBY_API ALobbyPawn : public APawn
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta=(AllowPrivateAccess = "true"))
	class USceneComponent* SceneComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta=(AllowPrivateAccess = "true"))
	class USkeletalMeshComponent* SkeletalMeshComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta=(AllowPrivateAccess = "true"))
	class UWidgetComponent* WidgetComponent;
	TSubclassOf<class UUserWidget> PlayerNameWidgetClass;

	bool IsFullyInitialized = false;

public:
	ALobbyPawn(const FObjectInitializer& ObjectInitializer);
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void OnPlayerNameLocalChanged(FString NewPlayerNameLocal);
	UFUNCTION(Server, WithValidation, Unreliable)
	void UpdateName();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	

};
