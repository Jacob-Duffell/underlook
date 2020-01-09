// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PickupBase.generated.h"

class USphereComponent;
class UPrimitiveComponent;

UCLASS()
class GEP_COURSEWORK_SEM2_API APickupBase : public AActor
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, Category = "Components")
	USphereComponent* SphereComp;
	
public:	
	// Sets default values for this actor's properties
	APickupBase();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup")
	float maxDeactivateTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup")
	float deactivateTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup")
	bool deactivated;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void NotifyActorBeginOverlap(AActor* otherActor);

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION(BlueprintImplementableEvent, Category = "Pickup")
	void OnActivate(AActor* pickedUpBy);

	UFUNCTION(BlueprintImplementableEvent, Category = "Pickup")
	void DeactivatePickup();
	
};
