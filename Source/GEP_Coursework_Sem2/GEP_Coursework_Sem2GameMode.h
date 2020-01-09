// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GEP_Coursework_Sem2GameMode.generated.h"

UCLASS(minimalapi)
class AGEP_Coursework_Sem2GameMode : public AGameModeBase
{
	GENERATED_BODY()

protected:

	UFUNCTION(BlueprintImplementableEvent)
		void OnGameStart();

	UFUNCTION(BlueprintImplementableEvent)
		void OnCharacterKilled(AUnderlookCharacter* killedCharacter, AActor* killedBy);

	UFUNCTION(BlueprintImplementableEvent)
		void OnGameEnd(int winningTeamID);

	UFUNCTION(BlueprintImplementableEvent)
		void OnObjectiveComplete(int teamID, AUnderlookCharacter* completedBy);

public:
	AGEP_Coursework_Sem2GameMode();

	UFUNCTION(BlueprintCallable)
		void LevelSetupComplete();

	UFUNCTION(BlueprintCallable)
		void CharacterKilled(class AUnderlookCharacter* killedCharacter, AActor* killedBy);

	UFUNCTION(BlueprintCallable)
		void GameOver(int winningTeamID);

	UFUNCTION(BlueprintCallable)
		void ObjectiveComplete(int teamID, AUnderlookCharacter* completedBy);
};



