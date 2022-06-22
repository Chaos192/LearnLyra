// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "LyraAbilitySystemComponent.generated.h"

/**
 *
 */
UCLASS()
class LYRAGAME_API ULyraAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:

	ULyraAbilitySystemComponent(const FObjectInitializer& ObjectInitializer);

	void AbilityInputTagPressed(const FGameplayTag& InputTag);
	void AbilityInputTagReleased(const FGameplayTag& InputTag);

	void ProcessAbilityInput(float DeltaTime, bool bGamePaused);

protected:

	virtual void AbilitySpecInputPressed(FGameplayAbilitySpec& Spec) override;
	virtual void AbilitySpecInputReleased(FGameplayAbilitySpec& Spec) override;

protected:

	// 这一帧按下的GA的handle
	TArray<FGameplayAbilitySpecHandle> InputPressedSpecHandles;

	// 这一帧松开的GA的handle
	TArray<FGameplayAbilitySpecHandle> InputReleasedSpecHandles;

	// 按住的GA的handle
	TArray<FGameplayAbilitySpecHandle> InputHeldSpecHandles;
};
