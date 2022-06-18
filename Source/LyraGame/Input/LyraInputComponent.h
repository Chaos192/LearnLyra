#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "LyraInputConfig.h"
#include "GameplayTagContainer.h"

#include "LyraInputComponent.generated.h"

/**
 * 配置 UInputSettings::DefaultInputComponentClass
 * 在 APlayerController::SetupInputComponent() 中创建
 * 调用内置函数 IEnhancedInputSubsystemInterface::AddPlayerMappableConfig() 绑定FKey到UInputAction的映射
 * 调用内置函数 UEnhancedInputComponent::BindAction() 绑定UInputAction到代理函数
 */
UCLASS()
class LYRAGAME_API ULyraInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()

public:

	ULyraInputComponent(const FObjectInitializer& ObjectInitializer);

	// 应用ULyraSettingsLocal::RegisteredInputConfigs中储存的FKey到InputAction的映射
	void AddInputMappings(const ULyraInputConfig* InputConfig, UEnhancedInputLocalPlayerSubsystem* InputSubsystem);

	// 根据GameplayTag,找到InputData_Hero中配置的InputAction
	// 然后将InputAction绑定到回调函数
	// 这里其实是将GameplayTag到回调函数的映射写死
	template<class UserClass, typename FuncType>
	void BindNativeAction(const ULyraInputConfig* InputConfig, const FGameplayTag& InputTag, ETriggerEvent TriggerEvent, UserClass* Object, FuncType Func, bool bLogIfNotFound);
};

template<class UserClass, typename FuncType>
void ULyraInputComponent::BindNativeAction(const ULyraInputConfig* InputConfig, const FGameplayTag& InputTag, ETriggerEvent TriggerEvent, UserClass* Object, FuncType Func, bool bLogIfNotFound)
{
	check(InputConfig);
	if (const UInputAction* IA = InputConfig->FindNativeInputActionForTag(InputTag, bLogIfNotFound))
	{
		// 内置函数,绑定UInputAction到代理函数
		BindAction(IA, TriggerEvent, Object, Func);
	}
}
