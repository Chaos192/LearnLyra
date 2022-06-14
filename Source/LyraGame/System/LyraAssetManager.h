// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "LyraAssetManagerStartupJob.h"
#include "LyraAssetManager.generated.h"

class ULyraPawnData;

/**
 * 设置DefaultEngine.ini, AssetManagerClassName
 */
UCLASS(config = Game)
class LYRAGAME_API ULyraAssetManager : public UAssetManager
{
	GENERATED_BODY()

public:

	ULyraAssetManager();

	static ULyraAssetManager& Get();

	// ~UAssetManager interface
	// 引擎启动时,UEngine::InitializeObjectReferences()创建AssetManager,并调用此函数进行初始化
	virtual void StartInitialLoading() override;
	// ~End of UAssetManager interface

	// 返回资产,如果不存在就同步加载
	template<typename AssetType>
	static AssetType* GetAsset(const TSoftObjectPtr<AssetType>& AssetPointer, bool bKeepInMemory = true);

	const ULyraPawnData* GetDefaultPawnData() const;

protected:

	static UObject* SynchronousLoadAsset(const FSoftObjectPath& AssetPath);

	UPROPERTY(config)
		TSoftObjectPtr<ULyraPawnData> DefaultPawnData;

private:

	// Flushes the StartupJobs array. Processes all startup work.
	void DoAllStartupJobs();

	void InitializeAbilitySystem();

	// The list of tasks to execute on startup. Used to track startup progress.
	TArray<FLyraAssetManagerStartupJob> StartupJobs;
};

template<typename AssetType>
AssetType* ULyraAssetManager::GetAsset(const TSoftObjectPtr<AssetType>& AssetPointer, bool bKeepInMemory /*= true*/)
{
	AssetType* LoadedAsset = nullptr;

	const FSoftObjectPath& AssetPath = AssetPointer.ToSoftObjectPath();

	if (AssetPath.IsValid())
	{
		LoadedAsset = AssetPointer.Get();
		if (!LoadedAsset)
		{
			LoadedAsset = Cast<AssetType>(SynchronousLoadAsset(AssetPath));
			ensureAlwaysMsgf(LoadedAsset, TEXT("Failed to load asset [%s]"), *AssetPointer.ToString());
		}

		if (LoadedAsset && bKeepInMemory)
		{
			//Get().AddLoadedAsset(Cast<UObject>(LoadedAsset));
		}
	}

	return LoadedAsset;
}
