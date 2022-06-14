// Fill out your copyright notice in the Description page of Project Settings.


#include "System/LyraAssetManager.h"
#include "Character/LyraPawnData.h"
#include "LyraLogChannels.h"
#include "Stats/StatsMisc.h"
#include "LyraGameplayTags.h"
#include "AbilitySystemGlobals.h"

#define STARTUP_JOB_WEIGHTED(JobFunc, JobWeight) StartupJobs.Add(FLyraAssetManagerStartupJob(#JobFunc, [this](const FLyraAssetManagerStartupJob& StartupJob, TSharedPtr<FStreamableHandle>& LoadHandle){JobFunc;}, JobWeight))
#define STARTUP_JOB(JobFunc) STARTUP_JOB_WEIGHTED(JobFunc, 1.0f)

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

void ULyraAssetManager::StartInitialLoading()
{
	// OnAssetManagerCreatedDelegate 代理绑定UGameFeaturesSubsystem::OnAssetManagerCreated
	// 间接调用 UGameFeatureAction_AddInputConfig::OnGameFeatureRegistering
	Super::StartInitialLoading();

	STARTUP_JOB(InitializeAbilitySystem());

	DoAllStartupJobs();
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

void ULyraAssetManager::DoAllStartupJobs()
{
	if (IsRunningDedicatedServer())
	{
		// 先不管DS
	}
	else
	{
		if (StartupJobs.Num() > 0)
		{
			// 先不管加载进度(可能是用于UI显示加载百分比的)和权重

			for (FLyraAssetManagerStartupJob& StartupJob : StartupJobs)
			{
				StartupJob.DoJob();
			}
		}
	}

	StartupJobs.Empty();
}

void ULyraAssetManager::InitializeAbilitySystem()
{
	FLyraGameplayTags::InitializeNativeTags();

	// 必须调用InitGlobalData()来使用TargetData
	UAbilitySystemGlobals::Get().InitGlobalData();
}
