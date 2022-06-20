#include "LyraGameplayTags.h"
#include "GameplayTagsManager.h"

FLyraGameplayTags FLyraGameplayTags::GameplayTags;

void FLyraGameplayTags::InitializeNativeTags()
{
	UGameplayTagsManager& Manager = UGameplayTagsManager::Get();

	GameplayTags.AddAllTags(Manager);

	// Notify manager that we are done adding native tags.
	// 里面会重新构建GameplayTag Tree
	Manager.DoneAddingNativeTags();
}

void FLyraGameplayTags::AddAllTags(UGameplayTagsManager& Manager)
{
	AddTag(InputTag_Move, "InputTag.Move", "Move input.");
	AddTag(InputTag_Look_Mouse, "InputTag.Look.Mouse", "Look (mouse) input.");
	AddTag(InputTag_Crouch, "InputTag.Crouch", "Crouch input.");
}

void FLyraGameplayTags::AddTag(FGameplayTag& OutTag, const ANSICHAR* TagName, const ANSICHAR* TagComment)
{
	// 这样注册,不会直接修改ini文件,但是编辑器启动后,这些注册的Tag都可以使用
	OutTag = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName(TagName),
		FString(TEXT("(Native) ")) + FString(TagComment)
	);
}

