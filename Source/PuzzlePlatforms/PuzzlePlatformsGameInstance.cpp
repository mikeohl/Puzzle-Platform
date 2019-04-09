// Fill out your copyright notice in the Description page of Project Settings.


#include "PuzzlePlatformsGameInstance.h"

#include "PlatformTrigger.h"

#include "Engine/Engine.h"
#include "GameFramework/PlayerController.h"
#include "UObject/ConstructorHelpers.h"
#include "Blueprint/UserWidget.h"

// Sets default values
UPuzzlePlatformsGameInstance::UPuzzlePlatformsGameInstance(const FObjectInitializer & ObjectInitializer)
{
	// Constructor for struct FClassFinder
	ConstructorHelpers::FClassFinder<UUserWidget> MainMenu_WBPClass(TEXT("/Game/MenuSystem/MainMenu_WBP"));
	
	if (MainMenu_WBPClass.Succeeded())
	{
		MenuClass = MainMenu_WBPClass.Class;
	}
}

// Set values to initialize
void UPuzzlePlatformsGameInstance::Init()
{
	if (!ensure(MenuClass)) { return; }
	UE_LOG(LogTemp, Warning, TEXT("Found class %s"), *MenuClass->GetName());
}

// Loads User Menu Widget - (Exec UFUNCTION)
void UPuzzlePlatformsGameInstance::LoadMenu()
{
	if (!ensure(MenuClass)) { return; }
	UUserWidget* Menu = CreateWidget<UUserWidget>(this, MenuClass);

	if (!ensure(Menu)) { return; }
	Menu->AddToViewport();

	APlayerController* PlayerController = GetFirstLocalPlayerController();
	if (!ensure(PlayerController)) { return; }

	FInputModeUIOnly InputModeBaseData;
	InputModeBaseData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputModeBaseData.SetWidgetToFocus(Menu->TakeWidget());
	
	PlayerController->bShowMouseCursor = true;
	PlayerController->SetInputMode(InputModeBaseData);
}

// Host a server and goto playable map - (Exec UFUNCTION)
void UPuzzlePlatformsGameInstance::Host()
{
	// Or use GetEngine function on GameInstance
	if (!ensure(GEngine)) { return; } 
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Hello World"));

	UWorld* World = GetWorld();
	if (!ensure(World)) { return; }

	World->ServerTravel("/Game/ThirdPersonBP/Maps/ThirdPersonExampleMap?listen");
}

// Join a server and goto playable map - (Exec UFUNCTION)
void UPuzzlePlatformsGameInstance::Join(const FString& Address)
{
	// Or use GetEngine function on GameInstance
	if (!ensure(GEngine)) { return; }
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("Joining: %s"), *Address));

	APlayerController* PlayerController = GetFirstLocalPlayerController();
	if (!ensure(PlayerController)) { return; }

	PlayerController->ClientTravel(*Address, TRAVEL_Absolute);
}


/**
 * Logging and Test code used to debug
 * 
 * UE_LOG(LogTemp, Warning, TEXT("UPuzzlePlatformsGameInstance Constructor Called"));
 * UE_LOG(LogTemp, Warning, TEXT("UPuzzlePlatformsGameInstance Init Called"));
 */