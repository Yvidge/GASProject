// Copyright Epic Games, Inc. All Rights Reserved.

#include "GASProjectGameMode.h"
#include "GASProjectCharacter.h"
#include "UObject/ConstructorHelpers.h"

AGASProjectGameMode::AGASProjectGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
