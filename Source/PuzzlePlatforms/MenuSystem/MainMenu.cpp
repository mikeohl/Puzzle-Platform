// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenu.h"

#include "UMG/Public/Components/Button.h"

bool UMainMenu::Initialize()
{
	bool bSucceeded = Super::Initialize();
	if (!bSucceeded) { return false; }

	if (!ensure(HostButton)) { return false; }
	HostButton->OnClicked.AddDynamic(this, &UMainMenu::HostServer);

	//if (!ensure(JoinButton)) { return false; }
	//JoinButton->OnClicked.AddDynamic(this, &UMainMenu::JoinServer);

	AddToViewport();
	
	return true;
}


void UMainMenu::HostServer()
{
	if (!ensure(MenuInterface)) { return; }
	MenuInterface->Host();
	RemoveFromViewport();
}


void UMainMenu::JoinServer(FString Address)
{
	RemoveFromViewport();
}



/**
 * Logging and Test code used to debug + Legacy code
 *
 * UE_LOG(LogTemp, Warning, TEXT("UPuzzlePlatformsGameInstance Constructor Called"));
 * UE_LOG(LogTemp, Warning, TEXT("UPuzzlePlatformsGameInstance Init Called"));
 *
 * ++++++++++++++++ LEGACY CODE +++++++++++++++++++
 * UPuzzlePlatformsGameInstance* GameInstance = Cast<UPuzzlePlatformsGameInstance>(GetGameInstance());
 *	if (!ensure(GameInstance)) { return; }
 *	GameInstance->Host();
 */