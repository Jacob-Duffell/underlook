// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "HealthComponent.h"
#include "IDamageable.h"
#include "UnderlookCharacter.generated.h"

UCLASS()
class GEP_COURSEWORK_SEM2_API AUnderlookCharacter : public ACharacter, public IIDamageable
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AUnderlookCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Health")
		class UHealthComponent* Health;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Gameplay")
		int TeamID;

	UPROPERTY(BlueprintReadWrite, Category = "Gameplay")
		bool CanRespawn = true;		// Default to true until challenge attempted

private:

	bool WaitingToRespawn;
	float RespawnTime;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Damage")
		bool OnHit();
		virtual bool OnHit_Implementation() override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Damage")
		bool OnDeath();
		virtual bool OnDeath_Implementation() override;

	UFUNCTION(BlueprintCallable)
		int GetTeamID();
	
	UFUNCTION(BlueprintCallable)
		void SetTeamID(int newTeamID);

	UFUNCTION(BlueprintCallable)
		void StartRespawnTimer(float timeToRespawn);

	UFUNCTION(BlueprintCallable)
		void InitCharacter();

	UFUNCTION(BlueprintImplementableEvent)
		void InitialiseCharacter();

	void OnAnyDamage();
};
