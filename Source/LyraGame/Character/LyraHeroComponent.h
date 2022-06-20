// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/LyraPawnComponent.h"
#include "InputActionValue.h"

#include "LyraHeroComponent.generated.h"

class UInputComponent;

/**
 * B_Hero_ShooterMannequin继承的B_Hero_Default蓝图挂载的组件
 */
UCLASS(Blueprintable, meta = (BlueprintSpawnableComponent))
class LYRAGAME_API ULyraHeroComponent : public ULyraPawnComponent
{
	GENERATED_BODY()

public:
	ULyraHeroComponent(const FObjectInitializer& ObjectInitializer);

protected:

	virtual void OnRegister() override;

	void OnPawnReadyToInitialize();

	virtual void InitializePlayerInput(UInputComponent* PlayerInputComponent);

	void Input_Move(const FInputActionValue& InputActionValue);
	void Input_LookMouse(const FInputActionValue& InputActionValue);
	void Input_Crouch(const FInputActionValue& InputActionValue);

	// True when the pawn has fully finished initialization
	bool bPawnHasInitialized;

	// True when player input bindings have been applyed, will never be true for non-players
	bool bReadyToBindInputs;
};
