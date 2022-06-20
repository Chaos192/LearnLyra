#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"

class UGameplayTagsManager;

/**
 * 包含GameplayTags的单例
 */
struct FLyraGameplayTags
{
public:

	static const FLyraGameplayTags& Get() { return GameplayTags; }

	static void InitializeNativeTags();

public:

	FGameplayTag InputTag_Move;
	FGameplayTag InputTag_Look_Mouse;
	FGameplayTag InputTag_Crouch;

protected:

	void AddAllTags(UGameplayTagsManager& Manager);
	void AddTag(FGameplayTag& OutTag, const ANSICHAR* TagName, const ANSICHAR* TagComment);

private:

	static FLyraGameplayTags GameplayTags;
};