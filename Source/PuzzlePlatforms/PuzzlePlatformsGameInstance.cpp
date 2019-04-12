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

// Loads User Menu Widget - (Exec UFUNCTION)
void UPuzzlePlatformsGameInstance::LoadMenu()
{
	if (!ensure(MainMenuClass)) { return; }
	MainMenu = CreateWidget<UMainMenu>(this, MainMenuClass);

	if (!ensure(MainMenu)) { return; }
	MainMenu->SetMenuInterface(this);

	SetInputToMenu();
}

void UPuzzlePlatformsGameInstance::LoadInGameMenu()
{
	if (!ensure(InGameMenuClass)) { return; }
	InGameMenu = CreateWidget<UInGameMenu>(this, InGameMenuClass);

	if (!ensure(InGameMenu)) { return; }
	InGameMenu->SetMenuInterface(this);

	SetInputToMenu();
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
	SetInputToGame();
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
	SetInputToGame();
	
}

// Set player controller input to default GameOnly
void UPuzzlePlatformsGameInstance::SetInputToGame()
{
	APlayerController* PlayerController = GetFirstLocalPlayerController();
	if (!ensure(PlayerController)) { return; }

	FInputModeGameOnly InputModeBaseData;
	PlayerController->bShowMouseCursor = false;
	PlayerController->SetInputMode(InputModeBaseData);

	PlayerController->InputComponent->BindAction("LoadInGameMenu", EInputEvent::IE_Pressed, this, &UPuzzlePlatformsGameInstance::LoadInGameMenu);
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
 *
 * +++++++++++ Legacy Code +++++++++++++
 * InputModeBaseData.SetWidgetToFocus(Menu->TakeWidget());
 */