#pragma once

#include "CoreMinimal.h"
#include "GameFeatureAction.h"
#include "Input/LyraMappableConfigPair.h"
#include "GameFeatureAction_AddInputConfig.generated.h"

/**
 * 将配置的FKey按键到InputAction的映射,储存到ULyraSettingsLocal::RegisteredInputConfigs
 *
 * 应使用EnhancedInput system
 */
UCLASS(meta = (DisplayName = "Add Input Config"))
class LYRAGAME_API UGameFeatureAction_AddInputConfig : public UGameFeatureAction
{
	GENERATED_BODY()

public:
	// ~UGameFeatureAction interface
	
	// 引擎启动时,ULyraAssetManager::StartInitialLoading()通过代理间接调用此函数
	virtual void OnGameFeatureRegistering() override;
	
	// 开始游戏时,ALyraGameMode::InitGame()设置下一帧定时器,间接调用ULyraExperienceManagerComponent::OnExperienceLoadComplete()
	// 里面会调用UGameFeaturesSubsystem::LoadAndActivateGameFeaturePlugin()
	virtual void OnGameFeatureActivating(FGameFeatureActivatingContext& Context) override;
	
	// ~End of UGameFeatureAction interface

	/** 将被注册的玩家可配置的按键映射 */
	UPROPERTY(EditAnywhere)
		TArray<FMappableConfigPair> InputConfigs;
};
