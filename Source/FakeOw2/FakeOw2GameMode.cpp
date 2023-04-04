// Copyright Epic Games, Inc. All Rights Reserved.

#include "FakeOw2GameMode.h"
#include "FakeOw2Character.h"
#include "UObject/ConstructorHelpers.h"

AFakeOw2GameMode::AFakeOw2GameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
