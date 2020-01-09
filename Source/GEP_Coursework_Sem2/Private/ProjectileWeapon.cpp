// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectileWeapon.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GEP_Coursework_Sem2Projectile.h"
#include "Particles/ParticleSystemComponent.h"

AProjectileWeapon::AProjectileWeapon()
{
	
}

bool AProjectileWeapon::FireWeapon()
{
	if (CurrentAmmo > 0)
	{
		if (FireInterval <= 0)
		{
			// try and fire a projectile
			if (ProjectileClass != NULL)
			{
				UWorld* const World = GetWorld();
				if (World != NULL)
				{
					CurrentAmmo -= 1;

					const FRotator SpawnRotation = UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetControlRotation();
					//MuzzleOffset is in camera space, so transform it to world space before offsetting from the character location to find the final muzzle position
					const FVector SpawnLocation = ((MuzzleLocation != nullptr) ? MuzzleLocation->GetComponentLocation() : GetActorLocation()) + SpawnRotation.RotateVector(GunOffset);

					// Set Spawn Collision Handling Override
					FActorSpawnParameters ActorSpawnParams;
					ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

					// Spawn the projectile at the muzzle
					World->SpawnActor<AGEP_Coursework_Sem2Projectile>(ProjectileClass, SpawnLocation, SpawnRotation, ActorSpawnParams);

					GetWorld()->GetFirstPlayerController()->ClientPlayCameraShake(FireCamShake);

					UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ShootEffect, MeshComp->GetSocketLocation("Muzzle"));

					FireInterval = RateOfFire;
				}
			}

			// try and play the sound if specified
			if (FireSound != NULL)
			{
				UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
			}

			return true;
		}
	}
	return false;
}