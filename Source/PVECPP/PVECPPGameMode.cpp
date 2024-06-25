// Copyright Epic Games, Inc. All Rights Reserved.

#include "PVECPPGameMode.h"
#include "PVECPPCharacter.h"
#include "UObject/ConstructorHelpers.h"

APVECPPGameMode::APVECPPGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
