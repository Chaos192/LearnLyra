// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModes/LyraGameMode.h"
#include "GameModes/LyraGameState.h"
#include "Player/LyraPlayerController.h"
#include "Player/LyraPlayerState.h"
#include "Character/LyraCharacter.h"
#include "UI/LyraHUD.h"

ALyraGameMode::ALyraGameMode(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	GameStateClass = ALyraGameState::StaticClass();
	PlayerControllerClass = ALyraPlayerController::StaticClass();
	PlayerStateClass = ALyraPlayerState::StaticClass();
	DefaultPawnClass = ALyraCharacter::StaticClass();
	HUDClass = ALyraHUD::StaticClass();
}
