// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayAbilitySpec.h"

#include "LyraAbilitySet.generated.h"

class ULyraAbilitySystemComponent;
class ULyraGameplayAbility;
class UGameplayEffect;

/**
 * AbilitySet使用的用于赋予GA的数据
 */
USTRUCT(BlueprintType)
struct FLyraAbilitySet_GameplayAbility
{
	GENERATED_BODY()

public:

	// 要赋予的GA
	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<ULyraGameplayAbility> Ability = nullptr;

	// 要赋予的GA等级
	UPROPERTY(EditDefaultsOnly)
		int32 AbilityLevel = 1;

	// 用于处理GA输入的Tag
	UPROPERTY(EditDefaultsOnly, meta = (Categories = "InputTag"))
		FGameplayTag InputTag;
};

/**
 * 用于储存AbilitySet赋予的GA的handle的数据
 */
USTRUCT(BlueprintType)
struct FLyraAbilitySet_GrantedHandles
{
	GENERATED_BODY()

public:

	void AddAbilitySpecHandle(const FGameplayAbilitySpecHandle& Handle);

protected:
	// 赋予的GA的handls
	UPROPERTY()
		TArray<FGameplayAbilitySpecHandle> AbilitySpecHandles;
};

/**
 * 用于赋予Gameplay Abilities和Gameplay Effects的常量数据资产
 */
UCLASS(BlueprintType, Const)
class LYRAGAME_API ULyraAbilitySet : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:

	ULyraAbilitySet(const FObjectInitializer& ObjectInitializer);

	// 将GA赋予ASC
	// 返回的handle可以用来取消赋予的GA
	void GiveToAbilitySystem(ULyraAbilitySystemComponent* LyraASC, FLyraAbilitySet_GrantedHandles* OutGrantedHandles, UObject* SourceObject = nullptr) const;

protected:

	// 当此Ability Set被赋予时,要赋予的GA
	/// [PropertyMetadata] Used by arrays of structs. Indicates a single property inside of the struct that should be used as a title summary when the array entry is collapsed.
	// TitleProperty: 对于结构体数组,在折叠里面的元素时,这个属性会显示为标题
	UPROPERTY(EditDefaultsOnly, Category = "Gameplay Abilities", meta = (TitleProperty = Ability))
		TArray<FLyraAbilitySet_GameplayAbility> GrantedGameplayAbilities;
};
