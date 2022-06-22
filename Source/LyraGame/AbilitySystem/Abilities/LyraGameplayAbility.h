#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"

#include "LyraGameplayAbility.generated.h"

class ULyraAbilitySystemComponent;

/**
 * 定义GA如何激活
 */
UENUM(BlueprintType)
enum class ELyraAbilityActivationPolicy : uint8
{
	// 按下按键时激活
	OnInputTriggered,

	// 按住按键时不断激活
	WhileInputActive,

	// 设置Avatar时激活
	OnSpawn
};

UCLASS(Abstract, hideCategories = Input, meta = (ShortToolTip = "此项目的Gameplay Ability基类"))
class ULyraGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

public:

	friend class ULyraAbilitySystemComponent;

	ULyraGameplayAbility(const FObjectInitializer& ObjectInitializer);

	ELyraAbilityActivationPolicy GetActivationPolicy() const
	{
		return ActivationPolicy;
	}

protected:

	// 定义GA如何激活
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Lyra|Ability Activation")
		ELyraAbilityActivationPolicy ActivationPolicy;
};