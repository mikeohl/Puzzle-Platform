// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "MenuInterface.generated.h"

class UUserWidget;

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UMenuInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class PUZZLEPLATFORMS_API IMenuInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void LoadMenu() = 0;
	virtual void LoadInGameMenu() = 0;

	virtual void SetInputToGame() = 0;
	virtual void SetInputToMenu() = 0;

	virtual void Host() = 0;
	virtual void Join(const FString& Address) = 0;
	virtual void Leave() = 0;
	virtual void QuitGame() = 0;

protected:
	TSubclassOf<UUserWidget> MainMenuClass = nullptr;
	TSubclassOf<UUserWidget> InGameMenuClass = nullptr;
	
	class UInGameMenu* InGameMenu = nullptr;
	class UMainMenu* MainMenu = nullptr;
};
