#include "Input/LyraInputComponent.h"
#include "Player/LyraLocalPlayer.h"
#include "Settings/LyraSettingsLocal.h"
//#include "EnhancedInputSubsystemInterface.h"

ULyraInputComponent::ULyraInputComponent(const FObjectInitializer& ObjectInitializer)
{

}

void ULyraInputComponent::AddInputMappings(const ULyraInputConfig* InputConfig, UEnhancedInputLocalPlayerSubsystem* InputSubsystem)
{
	// InputConfig: InputData_Hero, 配置InputAction到GameplayTag的映射
	check(InputConfig);
	check(InputSubsystem);

	ULyraLocalPlayer* LocalPlayer = InputSubsystem->GetLocalPlayer<ULyraLocalPlayer>();
	check(LocalPlayer);

	// 应用ULyraSettingsLocal::RegisteredInputConfigs中储存的FKey到InputAction的映射
	if (ULyraSettingsLocal* LocalSettings = ULyraSettingsLocal::Get())
	{
		// 不忽略添加按键映射时按下的按键
		// 这允许你死亡时按住移动按键,直到重生,重生后会立刻应用移动
		// 如果bIgnoreAllPressedKeysUntilRelease设为默认值true,要求玩家松开移动按键,重生后重新按下
		FModifyContextOptions Options = {};
		Options.bIgnoreAllPressedKeysUntilRelease = false;

		const TArray<FLoadedMappableConfigPair>& Configs = LocalSettings->GetAllRegisteredInputConfigs();
		for (const FLoadedMappableConfigPair& Pair : Configs)
		{
			if (Pair.bIsActive)
			{
				// Pair.Config: PMI_Default_KBM
				// Pair.Config.Contexts: IMC_Default_KBM, 配置按键到InputAction的映射
				// 内置函数,应用FKey(按键)到InputAction的映射
				InputSubsystem->AddPlayerMappableConfig(Pair.Config, Options);
			}
		}
	}
}
