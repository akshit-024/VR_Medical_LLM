// Copyright Epic Games, Inc. All Rights Reserved.

#include "MyProject7_vr_testGameMode.h"
#include "MyProject7_vr_testCharacter.h"
#include "UObject/ConstructorHelpers.h"

AMyProject7_vr_testGameMode::AMyProject7_vr_testGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
