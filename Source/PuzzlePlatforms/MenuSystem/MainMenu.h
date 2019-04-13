// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MenuInterface.h"
#include "MainMenu.generated.h"

/**
 * 
 */

class UButton;
class UWidget;
class UWidgetSwitcher;
class UEditableTextBox;

UCLASS()
class PUZZLEPLATFORMS_API UMainMenu : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual bool Initialize() override;

	void SetMenuInterface(IMenuInterface* Interface) { MenuInterface = Interface; }
	
private:
	UFUNCTION()
	void HostServer();

	UFUNCTION()
	void JoinServer();

	UFUNCTION()
	void OpenJoinMenu();

	UFUNCTION()
	void OpenSelectMenu();

	UFUNCTION()
	void QuitGame();

	UPROPERTY(meta = (BindWidget))
	UButton* JoinButton = nullptr;

	UPROPERTY(meta = (BindWidget))
	UButton* HostButton = nullptr;

	UPROPERTY(meta = (BindWidget))
	UButton* CancelButton = nullptr;

	UPROPERTY(meta = (BindWidget))
	UButton* JoinServerButton = nullptr;

	UPROPERTY(meta = (BindWidget))
	UButton* QuitGameButton = nullptr;

	UPROPERTY(meta = (BindWidget))
	UWidgetSwitcher* WidgetSwitcher = nullptr;

	UPROPERTY(meta = (BindWidget))
	UWidget* JoinMenu = nullptr;

	UPROPERTY(meta = (BindWidget))
	UWidget* SelectMenu = nullptr;

	UPROPERTY(meta = (BindWidget))
	UEditableTextBox* IPInputBox = nullptr;

	IMenuInterface* MenuInterface = nullptr;
};
