// Copyright Epic Games, Inc. All Rights Reserved.

#include "buildEscapeGameMode.h"
#include "buildEscapeHUD.h"
#include "buildEscapeCharacter.h"
#include "UObject/ConstructorHelpers.h"

AbuildEscapeGameMode::AbuildEscapeGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AbuildEscapeHUD::StaticClass();
}
