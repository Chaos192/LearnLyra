#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameUserSettings.h"
#include "CommonInputBaseTypes.h"
#include "Input/LyraMappableConfigPair.h"

#include "LyraSettingsLocal.generated.h"

class UPlayerMappableInputConfig;

/**
 * Stores user settings for a game (for example graphics and sound settings)
 * with the ability to save and load to and from a file.
 *
 * 这里储存了玩家的按键映射FKey -> InputAction
 */
UCLASS()
class ULyraSettingsLocal : public UGameUserSettings
{
	GENERATED_BODY()

public:

	ULyraSettingsLocal();

	static ULyraSettingsLocal* Get();

	/**
	 * 将指定按键映射储存到 ULyraSettingsLocal::RegisteredInputConfigs
	 */
	void RegisterInputConfig(ECommonInputType Type, const UPlayerMappableInputConfig* NewConfig, const bool bIsActive);

	void ActivateInputConfig(const UPlayerMappableInputConfig* Config);

	/** 获取注册的输入配置 */
	const TArray<FLoadedMappableConfigPair>& GetAllRegisteredInputConfigs()
	{
		return RegisteredInputConfigs;
	}

private:

	/**
	 * 当前注册的输入配置,由 game feature plugins 支持
	 * @see UGameFeatureAction_AddInputConfig
	 */
	UPROPERTY(VisibleAnywhere)
		TArray<FLoadedMappableConfigPair> RegisteredInputConfigs;
};