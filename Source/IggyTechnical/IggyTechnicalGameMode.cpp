// Copyright Epic Games, Inc. All Rights Reserved.

#include "IggyTechnicalGameMode.h"
#include "IggyTechnicalCharacter.h"
#include "UObject/ConstructorHelpers.h"

AIggyTechnicalGameMode::AIggyTechnicalGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
