// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseWeapon.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GEP_Coursework_Sem2Projectile.h"
#include "NPCBase.h"
#include "DrawDebugHelpers.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
ABaseWeapon::ABaseWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MeshComp"));
	RootComponent = MeshComp;

	//Default offset from the character location for projectiles to spawn
	GunOffset = FVector(100.0f, 0.0f, 10.0f);

	MuzzleLocation = CreateDefaultSubobject<USceneComponent>(TEXT("MuzzleLoc"));
	MuzzleLocation->SetupAttachment(MeshComp);
	MuzzleLocation->SetRelativeLocation(FVector(0.2f, 48.4f, -10.0f));
}

// Called when the game starts or when spawned
void ABaseWeapon::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ABaseWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (FireInterval >= 0)
	{
		FireInterval -= DeltaTime;
	}
}

bool ABaseWeapon::FireWeapon()
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

					//get the "owner" of the weapon, i.e the character holding it
					AActor* MyOwner = GetOwner();

					if (MyOwner)
					{
						//set the eye location and rotation by accessing the characters "Eyes view point" 
						//in 1st person this is the center of the viewport
						FVector EyeLocation;
						FRotator EyeRotation;
						MyOwner->GetActorEyesViewPoint(EyeLocation, EyeRotation);

						//set a vector of huge length(or as far as you want bullets to hit) from the eye location outwards
						FVector TraceEnd = EyeLocation + (EyeRotation.Vector() * 10000);

						//get the position of the muzzle of the gun
						FVector MuzzlePos = MuzzleLocation->GetComponentLocation();

						//set up params to ignore the character and the weapon
						FCollisionQueryParams QueryParams;
						QueryParams.AddIgnoredActor(MyOwner);
						QueryParams.AddIgnoredActor(this);
						QueryParams.bTraceComplex = true;

						//create a hit structure to store data about the trace
						FHitResult hit;

						//trace from the eye location to the trace end
						if (GetWorld()->LineTraceSingleByChannel(hit, EyeLocation, TraceEnd, ECC_Visibility, QueryParams))
						{
							//draw a red line if it hits anything
							//DrawDebugLine(GetWorld(), MuzzlePos, TraceEnd, FColor::Red, false, 1.0f, 0, 1.0f);
							//Get the hit actor from hit
							AActor* hitActor = hit.GetActor();
							//hitActor->Destroy();

							if (BeamEffect)
							{
								//Spawn the particle effect at the muzzle socket and store it in a variable
								UParticleSystemComponent* BeamComp = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), BeamEffect, MeshComp->GetSocketLocation("Muzzle"));

								//Set the vector parameter "BeamEnd" 
								//If the hit returns an actor set it to the impact point else set it to TraceEnd
								BeamComp->SetVectorParameter("BeamEnd", (hit.Actor != NULL) ? hit.ImpactPoint : TraceEnd);

								if (hitActor != NULL && hitActor->IsA(ANPCBase::StaticClass()))
								{
									UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitActorEffect, hit.ImpactPoint);
									UGameplayStatics::ApplyDamage(hitActor, Damage, MyOwner->GetInstigatorController(), MyOwner, DamageType);
									
								}

								//BeamComp->OnComponentHit.AddDynamic(this, &ABaseWeapon::OnHit);		// set up a notification for when this component hits something blocking
							}
						}
						else
						{
							//draw a white line if it does not hit anything
							//DrawDebugLine(GetWorld(), MuzzlePos, TraceEnd, FColor::White, false, 1.0f, 0, 1.0f);
						}

						GetWorld()->GetFirstPlayerController()->ClientPlayCameraShake(FireCamShake);

						UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ShootEffect, MeshComp->GetSocketLocation("Muzzle"));

						FireInterval = RateOfFire;
					}
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

void ABaseWeapon::Reload()
{
	CurrentAmmo = MaxAmmo;
}

void ABaseWeapon::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	// Only add impulse and destroy projectile if we hit a physics
	if ((OtherActor != NULL) && (OtherActor != this) && (OtherComp != NULL))
	{

		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitActorEffect, GetActorLocation());

		OtherActor->Destroy();
		Destroy();
	}
}
