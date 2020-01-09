// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseAbility.h"


// Sets default values
ABaseAbility::ABaseAbility()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MeshComp"));
	RootComponent = MeshComp;
}

// Called when the game starts or when spawned
void ABaseAbility::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ABaseAbility::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool ABaseAbility::IsActivated()
{
	if (UltimateMeterPercentage >= 1.0f)
	{
		UltimateActivated();

		UltimateMeterPercentage = 0;
		return true;
	}

	return false;
}

