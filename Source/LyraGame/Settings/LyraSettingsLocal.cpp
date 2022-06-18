#include "LyraSettingsLocal.h"

ULyraSettingsLocal::ULyraSettingsLocal()
{

}

ULyraSettingsLocal* ULyraSettingsLocal::Get()
{
	return GEngine ? CastChecked<ULyraSettingsLocal>(GEngine->GetGameUserSettings()) : nullptr;
}

void ULyraSettingsLocal::RegisterInputConfig(ECommonInputType Type, const UPlayerMappableInputConfig* NewConfig, const bool bIsActive)
{
	if (NewConfig)
	{
		const int32 ExistingConfigIndex = RegisteredInputConfigs.IndexOfByPredicate(
			[&NewConfig](const FLoadedMappableConfigPair& Pair)
			{
				return Pair.Config == NewConfig;
			}
		);

		if (ExistingConfigIndex == INDEX_NONE)
		{
			const int32 NumAdded = RegisteredInputConfigs.Add(
				FLoadedMappableConfigPair(NewConfig, Type, bIsActive)
			);
			if (NumAdded != INDEX_NONE)
			{
				// 广播,先不处理
			}
		}
	}
}

void ULyraSettingsLocal::ActivateInputConfig(const UPlayerMappableInputConfig* Config)
{
	if (Config)
	{
		const int32 ExistingConfigIndex = RegisteredInputConfigs.IndexOfByPredicate(
			[&Config](const FLoadedMappableConfigPair& Pair)
			{
				return Pair.Config == Config;
			}
		);

		if (ExistingConfigIndex != INDEX_NONE)
		{
			RegisteredInputConfigs[ExistingConfigIndex].bIsActive = true;
		}
	}
}

