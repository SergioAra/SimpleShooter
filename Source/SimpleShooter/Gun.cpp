// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"

#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AGun::AGun():
	MaxRange(1000.f),
	Damage(10.f)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(RootSceneComponent);

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(GetRootComponent());

}

void AGun::PullTrigger()
{
	if(MuzzleFlash)
	{
		UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, Mesh, TEXT("MuzzleFlashSocket"));
	}
	if(MuzzleSound)
	{
		UGameplayStatics::SpawnSoundAttached(MuzzleSound, Mesh, TEXT("MuzzleFlashSocket"));
	}
	
	FHitResult OutHitResult;
	FVector ShotDirection;
	if(GunTrace(OutHitResult, ShotDirection))
	{
		if(ImpactEffect)
		{
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactEffect, OutHitResult.Location, ShotDirection.Rotation());
		}
		if(ImpactSound)
		{
			UGameplayStatics::PlaySoundAtLocation(GetWorld(), ImpactSound, OutHitResult.Location, ShotDirection.Rotation());
		}
		
		AActor* HitActor = OutHitResult.GetActor();
		if(HitActor)
		{
			FPointDamageEvent DamageEvent(Damage, OutHitResult, ShotDirection, UDamageType::StaticClass());
			HitActor->TakeDamage(Damage, DamageEvent, GetOwnerController(), this);
		}
		
	}
	
}

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();
	
}

bool AGun::GunTrace(FHitResult& OutHitResult, FVector& OutShotDirection)
{
	AController* OwnerController = GetOwnerController();
	if(!OwnerController) return false;
	FVector ViewPointLocation;
	FRotator ViewPointRotation;
	OwnerController->GetPlayerViewPoint(ViewPointLocation, ViewPointRotation);

	FVector EndPoint = ViewPointLocation + ViewPointRotation.Vector() * MaxRange;

	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	Params.AddIgnoredActor(GetOwner());
	
	OutShotDirection = -ViewPointRotation.Vector();
	return GetWorld()->LineTraceSingleByChannel(OutHitResult, ViewPointLocation, EndPoint, ECC_GameTraceChannel1, Params);
}

AController* AGun::GetOwnerController() const
{
	return Cast<APawn>(GetOwner())->GetController();
}

// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

