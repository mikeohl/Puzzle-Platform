// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenu.h"

#include "UMG/Public/Components/Widget.h"
#include "UMG/Public/Components/Button.h"
#include "UMG/Public/Components/WidgetSwitcher.h"
#include "UMG/Public/Components/EditableTextBox.h"

bool UMainMenu::Initialize()
{
	bool bSucceeded = Super::Initialize();
	if (!bSucceeded) { return false; }

	if (!ensure(HostButton)) { return false; }
	HostButton->OnClicked.AddDynamic(this, &UMainMenu::HostServer);

	if (!ensure(JoinButton)) { return false; }
	JoinButton->OnClicked.AddDynamic(this, &UMainMenu::OpenJoinMenu);

	if (!ensure(CancelButton)) { return false; }
	CancelButton->OnClicked.AddDynamic(this, &UMainMenu::OpenSelectMenu);

	if (!ensure(JoinServerButton)) { return false; }
	JoinServerButton->OnClicked.AddDynamic(this, &UMainMenu::JoinServer);

	if (!ensure(QuitGameButton)) { return false; }
	QuitGameButton->OnClicked.AddDynamic(this, &UMainMenu::QuitGame);
	
	AddToViewport();
	
	return true;
}


void UMainMenu::HostServer()
{
	if (!ensure(MenuInterface)) { return; }
	MenuInterface->Host();
	RemoveFromViewport();
}


void UMainMenu::JoinServer()
{
	if (!ensure(IPInputBox)) { return; }
	MenuInterface->Join(IPInputBox->GetText().ToString());
	RemoveFromViewport();
}


void UMainMenu::OpenJoinMenu()
{
	if (!ensure(WidgetSwitcher && JoinMenu)) { return; }
	WidgetSwitcher->SetActiveWidget(JoinMenu);
}


void UMainMenu::OpenSelectMenu()
{
	if (!ensure(WidgetSwitcher && SelectMenu)) { return; }
	WidgetSwitcher->SetActiveWidget(SelectMenu);
}

void UMainMenu::QuitGame()
{
	if (!ensure(MenuInterface)) { return; }
	MenuInterface->QuitGame();
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