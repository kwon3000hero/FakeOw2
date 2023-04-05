// Copyright Epic Games, Inc. All Rights Reserved.

#include "FakeOw2GameMode.h"
#include "FakeOw2Character.h"
#include "UObject/ConstructorHelpers.h"
#include "FakeOw2.h"

AFakeOw2GameMode::AFakeOw2GameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;
	UE_LOG(LogTemp, Warning, TEXT("%s"), *CALLINFO);
	PRINT_CALLINFO();
	PRINT_LOG(TEXT("My Log: %s"), TEXT("FakeOw2"));

}
