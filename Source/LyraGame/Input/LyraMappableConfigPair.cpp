#include "Input/LyraMappableConfigPair.h"
#include "System/LyraAssetManager.h"
#include "Settings/LyraSettingsLocal.h"
#include "PlayerMappableInputConfig.h"

bool FMappableConfigPair::RegisterPair(const FMappableConfigPair& Pair)
{
	ULyraAssetManager& AssetManager = ULyraAssetManager::Get();

	if (ULyraSettingsLocal* Settings = ULyraSettingsLocal::Get())
	{
		// 注册配置的按键映射,但是不激活
		if (const UPlayerMappableInputConfig* LoadedConfig = AssetManager.GetAsset(Pair.Config))
		{
			Settings->RegisterInputConfig(Pair.Type, LoadedConfig, false);
			return true;
		}
	}

	return false;
}

bool FMappableConfigPair::ActivatePair(const FMappableConfigPair& Pair)
{
	ULyraAssetManager& AssetManager = ULyraAssetManager::Get();

	if (FMappableConfigPair::RegisterPair(Pair))
	{
		if (ULyraSettingsLocal* Settings = ULyraSettingsLocal::Get())
		{
			if (const UPlayerMappableInputConfig* LoadedConfig = AssetManager.GetAsset(Pair.Config))
			{
				Settings->ActivateInputConfig(LoadedConfig);
				return true;
			}
		}
	}
	
	return false;
}

