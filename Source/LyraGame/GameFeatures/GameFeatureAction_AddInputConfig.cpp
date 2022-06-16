#include "GameFeatures/GameFeatureAction_AddInputConfig.h"

void UGameFeatureAction_AddInputConfig::OnGameFeatureRegistering()
{
	Super::OnGameFeatureRegistering();

	// Pair.Config: PMI_Default_KBM
	// Pair.Config.Contexts: IMC_Default_KBM, 配置按键到InputAction的映射
	for (const FMappableConfigPair& Pair : InputConfigs)
	{
		FMappableConfigPair::RegisterPair(Pair);
	}
}

void UGameFeatureAction_AddInputConfig::OnGameFeatureActivating(FGameFeatureActivatingContext& Context)
{
	Super::OnGameFeatureActivating(Context);

	// Pair.Config: PMI_Default_KBM
	// Pair.Config.Contexts: IMC_Default_KBM, 配置按键到InputAction的映射
	for (const FMappableConfigPair& Pair : InputConfigs)
	{
		if (Pair.bShouldActivateAutomatically)
		{
			FMappableConfigPair::RegisterPair(Pair);
		}
	}
}

