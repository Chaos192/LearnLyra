#pragma once

#include "CoreMinimal.h"
#include "CommonInputBaseTypes.h"

#include "LyraMappableConfigPair.generated.h"

class UPlayerMappableInputConfig;

/**
 * A container to organize loaded player mappable configs to their CommonUI input type
 */
USTRUCT(BlueprintType)
struct FLoadedMappableConfigPair
{
	GENERATED_BODY()

public:

	FLoadedMappableConfigPair() = default;
	FLoadedMappableConfigPair(const UPlayerMappableInputConfig* InConfig, ECommonInputType InType, const bool InIsActive)
		:Config(InConfig),
		Type(InType),
		bIsActive(InIsActive)
	{

	}

	/**
	 * The player mappable input config that should be applied to the Enhanced Input subsystem
	 * 引擎内置类型,储存一套玩家的按键映射 FKey -> UInputAction
	 */
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
		const UPlayerMappableInputConfig* Config = nullptr;

	/** 引擎内置类型,包括: 键鼠,触摸,Gamepad */
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
		ECommonInputType Type = ECommonInputType::Count;

	/** If this config is currently active. A config is marked as active when it's owning GFA is active */
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
		bool bIsActive = false;
};

/**
 * A container to organize potentially unloaded player mappable configs to their CommonUI input type
 *
 * 储存 FKey -> InputAction 映射的自定义结构体
 * 可以向 ULyraSettingsLocal::RegisteredInputConfigs 中注册自定义的映射
 */
USTRUCT()
struct FMappableConfigPair
{
	GENERATED_BODY()

public:

	FMappableConfigPair() = default;

	/**
	 * 引擎内置类型,储存一套玩家的按键映射 FKey -> UInputAction
	 */
	UPROPERTY(EditAnywhere)
		TSoftObjectPtr<UPlayerMappableInputConfig> Config;

	/**
	 * 引擎内置类型,包括: 键鼠,触摸,Gamepad
	 */
	UPROPERTY(EditAnywhere)
		ECommonInputType Type = ECommonInputType::Count;

	/** 注册配置中的映射 */
	static bool RegisterPair(const FMappableConfigPair& Pair);
};