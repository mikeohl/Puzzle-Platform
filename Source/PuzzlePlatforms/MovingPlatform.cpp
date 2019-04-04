// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"

AMovingPlatform::AMovingPlatform()
{
	PrimaryActorTick.bCanEverTick = true;
	SetMobility(EComponentMobility::Movable);
}

void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();
	StartingLocation = GetActorLocation();
}

void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (HasAuthority()) 
	{
		MovePlatform(DeltaTime);
	}
}

void AMovingPlatform::MovePlatform(float DeltaTime)
{

	FVector UnitVectorX(1.0f, 0.0f, 0.0f);

	// Switch directions after 600 cm
	if (abs(GetActorLocation().X - StartingLocation.X) > 600.0f) 
	{
		PlatformSpeed *= -1.0f;
	}

	SetActorLocation(GetActorLocation() + UnitVectorX * PlatformSpeed * DeltaTime);
}