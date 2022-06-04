// Fill out your copyright notice in the Description page of Project Settings.


#include "System/LyraAssetManager.h"
#include "Character/LyraPawnData.h"
#include "LyraLogChannels.h"
#include "Stats/StatsMisc.h"

ULyraAssetManager::ULyraAssetManager()
{
	DefaultPawnData = nullptr;
}

ULyraAssetManager& ULyraAssetManager::Get()
{
	check(GEngine);

	if (ULyraAssetManager* Singleton = Cast<ULyraAssetManager>(GEngine->AssetManager))
	{
		return *Singleton;
	}

	UE_LOG(LogLyra, Fatal, TEXT("Invalid AssetManagerClassName in DefaultEngine.ini.  It must be set to LyraAssetManager!"));

	// 上面的致命错误阻止调用到这里
	return *NewObject<ULyraAssetManager>();
}

const ULyraPawnData* ULyraAssetManager::GetDefaultPawnData() const
{
	return  GetAsset(DefaultPawnData);
}

UObject* ULyraAssetManager::SynchronousLoadAsset(const FSoftObjectPath& AssetPath)
{
	if (AssetPath.IsValid())
	{
		//TUniquePtr<FScopeLogTime> LogTimePtr;

		if (UAssetManager::IsValid())
		{
			return UAssetManager::GetStreamableManager().LoadSynchronous(AssetPath, false);
		}

		// 如果资产管理器还没准备好
		return AssetPath.TryLoad();
	}

	return nullptr;
}
