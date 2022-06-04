// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ModularGameState.h"
#include "AbilitySystemInterface.h"
#include "LyraGameState.generated.h"

class ULyraExperienceManagerComponent;
class ULyraAbilitySystemComponent;

/**
 *
 */
UCLASS()
class LYRAGAME_API ALyraGameState : public AModularGameStateBase, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:

	ALyraGameState(const FObjectInitializer& ObjectInitializer);

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

private:
	UPROPERTY()
		ULyraExperienceManagerComponent* ExperienceManagerComponent;

	UPROPERTY(VisibleAnywhere)
		ULyraAbilitySystemComponent* AbilitySystemComponent;
};
