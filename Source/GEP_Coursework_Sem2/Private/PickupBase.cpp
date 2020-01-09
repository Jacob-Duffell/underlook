// Fill out your copyright notice in the Description page of Project Settings.

#include "PickupBase.h"
#include "Components/SphereComponent.h"


// Sets default values
APickupBase::APickupBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
}

// Called when the game starts or when spawned
void APickupBase::BeginPlay()
{
	Super::BeginPlay();

	SphereComp->OnComponentBeginOverlap.AddDynamic(this, &APickupBase::OnOverlapBegin);
	
}

// Called every frame
void APickupBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (deactivated == true)
	{
		if (deactivateTime > 0)
		{
			deactivateTime -= DeltaTime;
		}
		else
		{
			deactivated = false;
			deactivateTime = maxDeactivateTime;
		}
	}
}

void APickupBase::NotifyActorBeginOverlap(AActor * OtherActor)
{
	//OnActivate(OtherActor);
	UE_LOG(LogTemp, Warning, TEXT("PICKUP - NotifyActorBeginOverlap"));
}


void APickupBase::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("PICKUP - PRE OnBeginOverlap"));
	// Other Actor is the actor that triggered the event. Check that is not ourself.  
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr))
	{
		if (OtherComp->ComponentTags.Contains("PrimaryCollider"))
		{
			UE_LOG(LogTemp, Warning, TEXT("PICKUP - OnBeginOverlap"));

			if (deactivated == false)
			{
				OnActivate(OtherActor);
			}
		}

	}
}