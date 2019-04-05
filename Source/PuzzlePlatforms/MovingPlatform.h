// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "MovingPlatform.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEPLATFORMS_API AMovingPlatform : public AStaticMeshActor
{
	GENERATED_BODY()

public:
	AMovingPlatform();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	
	void MovePlatform(float DeltaTime);

private:
	UPROPERTY(EditAnywhere, Category = "Setup")
	float Speed = 1.0f;

	UPROPERTY(EditAnywhere, Category = "Setup", Meta = (MakeEditWidget = true))
	FVector TargetLocation; // Relative Position from object

	UPROPERTY(VisibleAnywhere, Category = "Movement Points")
	FVector StartLocation;

	UPROPERTY(VisibleAnywhere, Category = "Movement Points")
	FVector EndLocation;
};
