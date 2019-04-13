// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MenuSystem/MenuInterface.h"
#include "PuzzlePlatformsGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEPLATFORMS_API UPuzzlePlatformsGameInstance : public UGameInstance, public IMenuInterface
{
	GENERATED_BODY()

public:
	UPuzzlePlatformsGameInstance(const FObjectInitializer & ObjectInitializer);
	virtual void Init() override;

	// IMenuInterface overrides
	UFUNCTION(Exec, BlueprintCallable)
	virtual void LoadMenu() override;

	UFUNCTION(Exec, BlueprintCallable)
	virtual void LoadInGameMenu() override;

	virtual void Leave() override;
	virtual void QuitGame() override;

	UFUNCTION(Exec)
	virtual void Host() override;

	UFUNCTION(Exec)
	virtual void Join(const FString& Address) override;

private:
	virtual void SetInputToGame() override;
	virtual void SetInputToMenu() override;
};
