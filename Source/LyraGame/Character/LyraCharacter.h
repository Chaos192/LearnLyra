// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ModularCharacter.h"
#include "LyraCharacter.generated.h"

class ULyraPawnExtensionComponent;

/**
 *
 */
UCLASS()
class LYRAGAME_API ALyraCharacter : public AModularCharacter
{
	GENERATED_BODY()

public:

	ALyraCharacter(const FObjectInitializer& ObjectInitializer);

protected:

	// APawn::PawnClientRestart()调用
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Lyra|Character", Meta = (AllowPrivateAccess = "true"))
		ULyraPawnExtensionComponent* PawnExtComponent;

public:

	void ToggleCrouch();
};
