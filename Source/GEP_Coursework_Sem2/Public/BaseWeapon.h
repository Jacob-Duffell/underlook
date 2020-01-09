// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseWeapon.generated.h"

class USoundBase;

UCLASS()
class GEP_COURSEWORK_SEM2_API ABaseWeapon : public AActor
{
	GENERATED_BODY()
	
private:
	//UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	//	class USceneComponent* MuzzleLocation;
	

public:	
	// Sets default values for this actor's properties
	ABaseWeapon();

	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class USceneComponent* MuzzleLocation;

	/** Gun muzzle's offset from the characters location */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
	FVector GunOffset;

	UPROPERTY(EditDefaultsOnly, Category = "Gameplay")
	TSubclassOf<class UDamageType> DamageType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
	float Damage;

	/** Projectile class to spawn */
	UPROPERTY(EditDefaultsOnly, Category = Projectile)
	TSubclassOf<class AGEP_Coursework_Sem2Projectile> ProjectileClass;

	UPROPERTY(EditDefaultsOnly, Category = Effects)
	TSubclassOf<class UCameraShake> FireCamShake;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	int CurrentAmmo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	int MaxAmmo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	float RateOfFire;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
	float FireInterval;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Effects")
	UParticleSystem* BeamEffect;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		USkeletalMeshComponent* MeshComp;

	UPROPERTY(EditDefaultsOnly, Category = "FX")
		UParticleSystem* ShootEffect;

	UPROPERTY(EditDefaultsOnly, Category = "FX")
		UParticleSystem* HitActorEffect;

	/** Sound to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
	class USoundBase* FireSound;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual bool FireWeapon();
	
	/** Reloads the weapon. */
	void Reload();

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	USkeletalMeshComponent* GetWeaponMesh() { return MeshComp; }
	
};
