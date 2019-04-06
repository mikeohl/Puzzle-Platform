// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"

#include "Runtime/Core/Public/Math/TransformNonVectorized.h"

// Sets default values
AMovingPlatform::AMovingPlatform()
{
	PrimaryActorTick.bCanEverTick = true;
	SetMobility(EComponentMobility::Movable);
}

// Called when the game starts or when spawned
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

// Called every frame
void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (bCanMove && HasAuthority()) 
	{
		MovePlatform(DeltaTime);
	}
}

// Move platform to target location and back
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

// Set whether platform can move
void AMovingPlatform::SetCanMove(bool bMove)
{
	bMove ? Count++ : Count--;
	if (Count < 0) Count = 0;
	Count ? bCanMove = true : bCanMove = false;
}


/**
 * Logging and Test code used to debug
 *
 * UE_LOG(LogTemp, Warning, TEXT("CurrentDisplacement Vector: x: %f, y: %f, z: %f"), CurrentDisplacement.X, CurrentDisplacement.Y, CurrentDisplacement.Z)
 * UE_LOG(LogTemp, Warning, TEXT("CurrentDistance: %f"), CurrentDistance)
 */
