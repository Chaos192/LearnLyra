#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"

#include "LyraGameplayAbility.generated.h"

class ULyraAbilitySystemComponent;

UCLASS(Abstract, hideCategories = Input, meta = (ShortToolTip = "此项目的Gameplay Ability基类"))
class ULyraGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

public:

	friend class ULyraAbilitySystemComponent;

	ULyraGameplayAbility(const FObjectInitializer& ObjectInitializer);
};