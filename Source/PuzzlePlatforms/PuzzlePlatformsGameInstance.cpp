// Fill out your copyright notice in the Description page of Project Settings.


#include "PuzzlePlatformsGameInstance.h"

#include "PlatformTrigger.h"
#include "MenuSystem/MainMenu.h"
#include "MenuSystem/InGameMenu.h"

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
		MainMenuClass = MainMenu_WBPClass.Class;
	}

	ConstructorHelpers::FClassFinder<UUserWidget> InGameMenu_WBPClass(TEXT("/Game/MenuSystem/InGameMenu_WBP"));

	if (InGameMenu_WBPClass.Succeeded())
	{
		InGameMenuClass = InGameMenu_WBPClass.Class;
	}
}

// Set values to initialize
void UPuzzlePlatformsGameInstance::Init()
{
	if (!ensure(MainMenuClass)) { return; }
	UE_LOG(LogTemp, Warning, TEXT("Found class %s"), *MainMenuClass->GetName());

	if (!ensure(InGameMenuClass)) { return; }
	UE_LOG(LogTemp, Warning, TEXT("Found class %s"), *InGameMenuClass->GetName());
}

// Loads User Menu Widget (called in Blueprint by BeginPlay)
void UPuzzlePlatformsGameInstance::LoadMenu()
{
	if (!ensure(MainMenuClass)) { return; }
	MainMenu = CreateWidget<UMainMenu>(this, MainMenuClass);

	if (!ensure(MainMenu)) { return; }
	MainMenu->SetMenuInterface(this);

	SetInputToMenu();
}

// Load up and set input to the InGame Menu
void UPuzzlePlatformsGameInstance::LoadInGameMenu()
{
	if (!ensure(InGameMenuClass)) { return; }
	InGameMenu = CreateWidget<UInGameMenu>(this, InGameMenuClass);

	if (!ensure(InGameMenu)) { return; }
	InGameMenu->SetMenuInterface(this);

	SetInputToMenu();
}


// Host a server and goto playable map
void UPuzzlePlatformsGameInstance::Host()
{
	UWorld* World = GetWorld();
	if (!ensure(World)) { return; }

	World->ServerTravel("/Game/ThirdPersonBP/Maps/ThirdPersonExampleMap?listen");
	SetInputToGame();
}

// Join a server and goto playable map
void UPuzzlePlatformsGameInstance::Join(const FString& Address)
{
	APlayerController* PlayerController = GetFirstLocalPlayerController();
	if (!ensure(PlayerController)) { return; }

	PlayerController->ClientTravel(*Address, TRAVEL_Absolute);
	SetInputToGame();
}

// Leave the server (whether client or host) //TODO: More robust implementation for server to not abandon clients
void UPuzzlePlatformsGameInstance::Leave()
{
	APlayerController* PlayerController = GetFirstLocalPlayerController();
	if (!ensure(PlayerController)) { return; }

	PlayerController->ClientTravel("/Game/MenuSystem/MainMenu", TRAVEL_Absolute);
}

// Quit the game
void UPuzzlePlatformsGameInstance::QuitGame()
{
	APlayerController* PlayerController = GetFirstLocalPlayerController();
	if (!ensure(PlayerController)) { return; }

	PlayerController->ConsoleCommand("Quit");
	UE_LOG(LogTemp, Warning, TEXT("Quit Game Called"));
}


// Set player controller input to default GameOnly
void UPuzzlePlatformsGameInstance::SetInputToGame()
{
	APlayerController* PlayerController = GetFirstLocalPlayerController();
	if (!ensure(PlayerController)) { return; }

	FInputModeGameOnly InputModeBaseData;
	PlayerController->bShowMouseCursor = false;
	PlayerController->SetInputMode(InputModeBaseData);
}

// Reset player controller input to UIOnly with cursor for menu
void UPuzzlePlatformsGameInstance::SetInputToMenu()
{
	APlayerController* PlayerController = GetFirstLocalPlayerController();
	if (!ensure(PlayerController)) { return; }

	FInputModeUIOnly InputModeBaseData;
	InputModeBaseData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	PlayerController->bShowMouseCursor = true;
	PlayerController->SetInputMode(InputModeBaseData);
}




/**
 * Logging and Test code used to debug + Legacy code
 * 
 * UE_LOG(LogTemp, Warning, TEXT("UPuzzlePlatformsGameInstance Constructor Called"));
 * UE_LOG(LogTemp, Warning, TEXT("UPuzzlePlatformsGameInstance Init Called"));
 *
 * UE_LOG(LogTemp, Warning, TEXT("LoadInGameMenu Completed"));

 * Or use GetEngine function on GameInstance
 * if (!ensure(GEngine)) { return; }
 * GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("Joining: %s"), *Address));
 *
 * +++++++++++ Legacy Code +++++++++++++
 * InputModeBaseData.SetWidgetToFocus(Menu->TakeWidget());
 * PlayerController->InputComponent->BindAction("LoadInGameMenu", EInputEvent::IE_Pressed, this, &UPuzzlePlatformsGameInstance::LoadInGameMenu);
 */