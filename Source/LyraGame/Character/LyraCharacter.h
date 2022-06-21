// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ModularCharacter.h"
#include "AbilitySystemInterface.h"

#include "LyraCharacter.generated.h"

class ULyraPawnExtensionComponent;
class ULyraAbilitySystemComponent;

/**
 *
 */
UCLASS()
class LYRAGAME_API ALyraCharacter : public AModularCharacter,
	public IAbilitySystemInterface
{
	GENERATED_BODY()

public:

	ALyraCharacter(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable, Category = "Lyra|Character")
		ULyraAbilitySystemComponent* GetLyraAbilitySystemComponent();
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

protected:

	// APawn::PawnClientRestart()调用
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:

	virtual void OnAbilitySystemInitialized();

private:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Lyra|Character", Meta = (AllowPrivateAccess = "true"))
		ULyraPawnExtensionComponent* PawnExtComponent;

public:

	void ToggleCrouch();
};
