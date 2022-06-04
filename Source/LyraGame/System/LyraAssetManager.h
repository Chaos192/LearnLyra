// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
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

	// 返回资产,如果不存在就同步加载
	template<typename AssetType>
	static AssetType* GetAsset(const TSoftObjectPtr<AssetType>& AssetPointer, bool bKeepInMemory = true);

	const ULyraPawnData* GetDefaultPawnData() const;

protected:

	static UObject* SynchronousLoadAsset(const FSoftObjectPath& AssetPath);

	UPROPERTY(config)
		TSoftObjectPtr<ULyraPawnData> DefaultPawnData;
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
