// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuPlayerController.h"

void AMenuPlayerController::BeginPlay()
{
    Super::BeginPlay();
    
    bShowMouseCursor = true; 
    bEnableClickEvents = true; 
    bEnableMouseOverEvents = true;
    bAutoManageActiveCameraTarget = false;
    bFindCameraComponentWhenViewTarget = false;

    UE_LOG(LogTemp, Warning, TEXT("PlayerController BeginPlay"));
}
