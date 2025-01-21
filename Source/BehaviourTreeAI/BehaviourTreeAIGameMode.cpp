// Copyright Epic Games, Inc. All Rights Reserved.

#include "BehaviourTreeAIGameMode.h"
#include "BehaviourTreeAICharacter.h"
#include "UObject/ConstructorHelpers.h"

ABehaviourTreeAIGameMode::ABehaviourTreeAIGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
