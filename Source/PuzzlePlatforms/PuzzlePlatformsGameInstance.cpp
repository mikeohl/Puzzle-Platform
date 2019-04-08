// Fill out your copyright notice in the Description page of Project Settings.


#include "PuzzlePlatformsGameInstance.h"

#include "Engine/Engine.h"
#include "GameFramework/PlayerController.h"

// Sets default values
UPuzzlePlatformsGameInstance::UPuzzlePlatformsGameInstance(const FObjectInitializer & ObjectInitializer)
{
	UE_LOG(LogTemp, Warning, TEXT("UPuzzlePlatformsGameInstance Constructor Called"))
}

// Set values to initialize
void UPuzzlePlatformsGameInstance::Init()
{
	UE_LOG(LogTemp, Warning, TEXT("UPuzzlePlatformsGameInstance Init Called"))
}

// Exec UFUNCTION
void UPuzzlePlatformsGameInstance::Host()
{
	// Or use GetEngine function on GameInstance
	if (!ensure(GEngine)) { return; } 
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Hello World"));

	UWorld* World = GetWorld();
	if (!ensure(World)) { return; }

	World->ServerTravel("/Game/ThirdPersonBP/Maps/ThirdPersonExampleMap?listen");
}

// Exec UFUNCTION
void UPuzzlePlatformsGameInstance::Join(const FString& Address)
{
	// Or use GetEngine function on GameInstance
	if (!ensure(GEngine)) { return; }
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("Joining: %s"), *Address));

	APlayerController* PlayerController = GetFirstLocalPlayerController();
	if (!ensure(PlayerController)) { return; }

	PlayerController->ClientTravel(*Address, TRAVEL_Absolute);
}