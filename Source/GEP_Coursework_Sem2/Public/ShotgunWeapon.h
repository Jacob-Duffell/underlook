// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseWeapon.h"
#include "ShotgunWeapon.generated.h"

UCLASS()
class GEP_COURSEWORK_SEM2_API AShotgunWeapon : public ABaseWeapon
{
	GENERATED_BODY()

public:	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	int NumberOfBullets;

	// Sets default values for this actor's properties
	AShotgunWeapon();

	bool FireWeapon() override;
	
};
