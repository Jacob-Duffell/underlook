// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseAbility.generated.h"

UCLASS()
class GEP_COURSEWORK_SEM2_API ABaseAbility : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseAbility();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		USkeletalMeshComponent* MeshComp;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	bool IsActivated();

	// Blueprint event fired when ability activated
	UFUNCTION(BlueprintImplementableEvent, Category = "Ultimate")
	void UltimateActivated();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Meter")
	float UltimateMeterPercentage;

	USkeletalMeshComponent* GetUltimateMesh() { return MeshComp; }
};
