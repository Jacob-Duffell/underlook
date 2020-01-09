// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once 

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "GEP_Coursework_Sem2HUD.generated.h"

UCLASS()
class AGEP_Coursework_Sem2HUD : public AHUD
{
	GENERATED_BODY()

public:
	AGEP_Coursework_Sem2HUD();

	/** Primary draw call for the HUD */
	virtual void DrawHUD() override;

private:
	/** Crosshair asset pointer */
	class UTexture2D* CrosshairTex;

};

