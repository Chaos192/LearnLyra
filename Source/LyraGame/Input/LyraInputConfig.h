// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h"

#include "LyraInputConfig.generated.h"

class UInputAction;

USTRUCT(BlueprintType)
struct FLyraInputAction
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly)
		const UInputAction* InputAction = nullptr;

	// Categories = "InputTag": GameplayTag只能选InputTag.XXX
	UPROPERTY(EditDefaultsOnly, meta = (Categories = "InputTag"))
		FGameplayTag InputTag;
};

/**
 * 一个实例: InputData_Hero
 */
UCLASS()
class LYRAGAME_API ULyraInputConfig : public UDataAsset
{
	GENERATED_BODY()

public:

	ULyraInputConfig(const FObjectInitializer& ObjectInitializer);

	const UInputAction* FindNativeInputActionForTag(const FGameplayTag& InputTag, bool bLogNotFound = true) const;

public:
	// 玩家使用的输入事件,这些事件映射到GameplayTag,并且必须手动绑定
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (TitleProperty = "InputAction"))
		TArray<FLyraInputAction> NativeInputActions;

	// 玩家使用的输入事件,这些事件映射到GameplayTag,并且自动绑定到对应InputTag的GA
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (TitleProperty = "InputAction"))
		TArray<FLyraInputAction> AbilityInputActions;
};
