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
	void JoinServer(FString Address);

	UPROPERTY(meta = (BindWidget))
	UButton* JoinButton = nullptr;

	UPROPERTY(meta = (BindWidget))
	UButton* HostButton = nullptr;

	IMenuInterface* MenuInterface = nullptr;
};
