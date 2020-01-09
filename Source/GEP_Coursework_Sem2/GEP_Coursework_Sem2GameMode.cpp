// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "GEP_Coursework_Sem2GameMode.h"
#include "GEP_Coursework_Sem2HUD.h"
#include "GEP_Coursework_Sem2Character.h"
#include "UObject/ConstructorHelpers.h"

AGEP_Coursework_Sem2GameMode::AGEP_Coursework_Sem2GameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/Characters/PushyMcShoveface"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AGEP_Coursework_Sem2HUD::StaticClass();
}

void AGEP_Coursework_Sem2GameMode::LevelSetupComplete() 
{
	OnGameStart();
}

void AGEP_Coursework_Sem2GameMode::CharacterKilled(class AUnderlookCharacter* killedCharacter, AActor* killedBy)
{
	OnCharacterKilled(killedCharacter, killedBy);
}

void AGEP_Coursework_Sem2GameMode::GameOver(int winningTeamID)
{
	OnGameEnd(winningTeamID);
}

void AGEP_Coursework_Sem2GameMode::ObjectiveComplete(int teamID, AUnderlookCharacter* completedBy)
{
	OnObjectiveComplete(teamID, completedBy);
}