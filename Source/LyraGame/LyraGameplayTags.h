#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"

/**
 * 包含GameplayTags的单例
 */
struct FLyraGameplayTags
{
public:

	static const FLyraGameplayTags& Get() { return GameplayTags; }

	static void InitializeNativeTags();

private:

	static FLyraGameplayTags GameplayTags;
};