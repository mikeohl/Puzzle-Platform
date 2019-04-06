// Fill out your copyright notice in the Description page of Project Settings.


#include "PlatformTrigger.h"

#include "MovingPlatform.h"
#include "Components/BoxComponent.h"

// Sets default values
APlatformTrigger::APlatformTrigger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Trigger = CreateDefaultSubobject<UBoxComponent>("Trigger");

	if (!ensure(Trigger)) { return; }
	RootComponent = Trigger;

	Trigger->OnComponentBeginOverlap.AddDynamic(this, &APlatformTrigger::OnOverlapBegin);
	Trigger->OnComponentEndOverlap.AddDynamic(this, &APlatformTrigger::OnOverlapEnd);
}

// Called when the game starts or when spawned
void APlatformTrigger::BeginPlay()
{
	Super::BeginPlay();

	// Turn off movement on connected platforms to start
	for (AMovingPlatform* Platform : ConnectedPlatforms)
	{
		if (!ensure(Platform)) { return; }
		Platform->SetCanMove(false);
	}
}

// Called every frame
void APlatformTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Dynamic delegate called on overlap
void APlatformTrigger::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Overlap detected"))
	TriggerCount++;

	if (TriggerCount <= 1)
	{
		for (AMovingPlatform* Platform : ConnectedPlatforms)
		{
			if (!ensure(Platform)) { return; }
			Platform->SetCanMove(true);
		}
	}
}

// Dynamic delegate called on end of overlap
void APlatformTrigger::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	TriggerCount--;
	UE_LOG(LogTemp, Warning, TEXT("Overlap ended"))

	if (TriggerCount <= 0)
	{
		for (AMovingPlatform* Platform : ConnectedPlatforms)
		{
			if (!ensure(Platform)) { return; }
			Platform->SetCanMove(false);
		}
	}
}

