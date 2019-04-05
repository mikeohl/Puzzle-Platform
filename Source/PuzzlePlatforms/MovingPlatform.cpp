// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"
#include "Runtime/Core/Public/Math/TransformNonVectorized.h"

AMovingPlatform::AMovingPlatform()
{
	PrimaryActorTick.bCanEverTick = true;
	SetMobility(EComponentMobility::Movable);

	//TargetLocation = FVector(0.0f);
}

void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority())
	{
		SetReplicates(true);
		SetReplicateMovement(true);
	}

	StartLocation = GetActorLocation();
	EndLocation = GetTransform().TransformPosition(TargetLocation);
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
	FVector InitialDisplacement = EndLocation - StartLocation;
	float InitialDistance = InitialDisplacement.SizeSquared();

	FVector CurrentDisplacement = EndLocation - GetActorLocation();
	float CurrentDistance = CurrentDisplacement.SizeSquared();
	
	
	// Switch directions reaching the target location
	if (CurrentDistance > InitialDistance || FVector::DotProduct(InitialDisplacement, CurrentDisplacement) < 0.0f)
	{
		Speed *= -1.0f;
	}

	SetActorLocation(GetActorLocation() + InitialDisplacement.GetSafeNormal() * Speed * DeltaTime);
}



/**
 * Unreal Logging used to debug
 *
 * UE_LOG(LogTemp, Warning, TEXT("CurrentDisplacement Vector: x: %f, y: %f, z: %f"), CurrentDisplacement.X, CurrentDisplacement.Y, CurrentDisplacement.Z)
 * UE_LOG(LogTemp, Warning, TEXT("CurrentDistance: %f"), CurrentDistance)
 */
