// Fill out your copyright notice in the Description page of Project Settings.

#include "LobbyPawn.h"

#include "InputCore.h"

#include "Components/InputComponent.h"
#include "Components/WidgetComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/SceneComponent.h"
#include "MultiplayerLobby/PlayerStates/PlayerStateBase.h"
#include "MultiplayerLobby/UI/LobbyPlayerNameWidget.h"

ALobbyPawn::ALobbyPawn(const FObjectInitializer& ObjectInitializer)
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(FName("Root"));
	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(FName("PlayerMesh"));
	WidgetComponent = CreateDefaultSubobject<UWidgetComponent>(FName("PlayerName"));
	
	RootComponent = SceneComponent;
	SkeletalMeshComponent->SetupAttachment(RootComponent);
	WidgetComponent->SetupAttachment(RootComponent);

	static ConstructorHelpers::FClassFinder<UUserWidget> PlayerNameBPClass(TEXT("/Game/UI/BP_PlayerName"));
	if (PlayerNameBPClass.Class != nullptr)
	{
		PlayerNameWidgetClass = PlayerNameBPClass.Class;
	}
}

// Called when the game starts or when spawned
void ALobbyPawn::BeginPlay()
{
	Super::BeginPlay();
	
	APlayerStateBase* MenuPlayerState = GetPlayerState<APlayerStateBase>();
	ULobbyPlayerNameWidget* Widget = CreateWidget<ULobbyPlayerNameWidget>(GetWorld(), PlayerNameWidgetClass);

	//This should be done in a method called by the server when the playername is fetched
	if(MenuPlayerState != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerNameLocal: %s"), *MenuPlayerState->PlayerNameLocal)
		Widget->SetPlayerName(MenuPlayerState->PlayerNameLocal);
	} else
	{
		UE_LOG(LogTemp, Warning, TEXT("LobbyPawn PlayerState is null"))
	}

	if(WidgetComponent != nullptr && Widget != nullptr)
	{
		WidgetComponent->SetWidget(Widget);
	}
}

// Called every frame
void ALobbyPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	/* ============= THIS IS UGLY AS FUCK ============= */
	if(!IsFullyInitialized)
	{
		if(WidgetComponent != nullptr)
		{
			APlayerStateBase* PawnPlayerState = GetPlayerState<APlayerStateBase>();
			if(PawnPlayerState != nullptr)
			{
				ULobbyPlayerNameWidget* Widget = Cast<ULobbyPlayerNameWidget>(WidgetComponent->GetWidget());
				Widget->SetPlayerName(PawnPlayerState->PlayerNameLocal);
				IsFullyInitialized = true;
			}
		
		}
	}
}

// Called to bind functionality to input
void ALobbyPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindKey(EKeys::E, IE_Released, this, &ALobbyPawn::UpdateName);
}

/*
* ==========================================================================================================
*                               Function called on playerstate property replication
* ==========================================================================================================
*/

void ALobbyPawn::OnPlayerNameLocalChanged(FString NewPlayerNameLocal)
{
	UE_LOG(LogTemp, Warning, TEXT("Setting name called by PlayerState: %s"), *NewPlayerNameLocal);
	if(this != nullptr)
	{
		if(WidgetComponent != nullptr)
		{
			ULobbyPlayerNameWidget* Widget = Cast<ULobbyPlayerNameWidget>(WidgetComponent->GetWidget());
			Widget->SetPlayerName(NewPlayerNameLocal);
		}
	}else
	{
		UE_LOG(LogTemp, Warning, TEXT("Pawn is null on: %s"), *NewPlayerNameLocal);
	}
}

/*
 * ==========================================================================================================
 *                                               Server Commands
 * ==========================================================================================================
 */
void ALobbyPawn::UpdateName_Implementation()
{
	if(HasAuthority()){
		APlayerStateBase* MenuPlayerState = GetPlayerState<APlayerStateBase>();
		MenuPlayerState->PlayerNameLocal = "Orion";
		MenuPlayerState->OnRep_PlayerNameLocal();
	}
}

bool ALobbyPawn::UpdateName_Validate()
{
	return true;
}

