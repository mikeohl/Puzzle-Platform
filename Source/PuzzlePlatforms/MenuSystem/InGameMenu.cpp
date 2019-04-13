// Fill out your copyright notice in the Description page of Project Settings.


#include "InGameMenu.h"

#include "Components/Button.h"


bool UInGameMenu::Initialize()
{
	UE_LOG(LogTemp, Warning, TEXT("Initialize Called"));
	bool bSucceeded = Super::Initialize();
	if (!bSucceeded) { return false; }

	if (!ensure(MainMenuButton)) { return false; }
	MainMenuButton->OnClicked.AddDynamic(this, &UInGameMenu::LoadMainMenu);

	if (!ensure(CancelButton)) { return false; }
	CancelButton->OnClicked.AddDynamic(this, &UInGameMenu::CloseInGameMenu);

	AddToViewport();
	
	return true;
}


void UInGameMenu::LoadMainMenu()
{
	RemoveFromViewport();

	if (!ensure(MenuInterface)) { return; }
	MenuInterface->Leave();
}


void UInGameMenu::CloseInGameMenu()
{
	RemoveFromViewport();

	if (!ensure(MenuInterface)) { return; }
	MenuInterface->SetInputToGame();
}


/**
 * Logging and Test code used to debug + Legacy code
 *
 * UE_LOG(LogTemp, Warning, TEXT("Called LoadMainMen()"));
 * UE_LOG(LogTemp, Warning, TEXT("Called CloseInGameMenu()"));
 *
 * ++++++++++++++++ LEGACY CODE +++++++++++++++++++
 * 
 */