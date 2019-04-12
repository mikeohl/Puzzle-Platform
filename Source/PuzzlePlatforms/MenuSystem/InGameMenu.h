// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MenuInterface.h"
#include "InGameMenu.generated.h"

class UButton;

/**
 * 
 */
UCLASS()
class PUZZLEPLATFORMS_API UInGameMenu : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual bool Initialize() override;

	void SetMenuInterface(IMenuInterface* Interface) { MenuInterface = Interface; }

	UFUNCTION()
	void LoadMainMenu(); //TODO: Leave server and load MainMenu level
	
	UFUNCTION()
	void CloseInGameMenu(); //TODO: Close in-game menu 

private:
	UPROPERTY(meta = (BindWidget))
	UButton* MainMenuButton = nullptr;

	UPROPERTY(meta = (BindWidget))
	UButton* CancelButton = nullptr;

	IMenuInterface* MenuInterface = nullptr;
};
