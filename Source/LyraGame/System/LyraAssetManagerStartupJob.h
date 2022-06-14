#pragma once

#include "CoreMinimal.h"
#include "Engine/StreamableManager.h"

/** Handles reporting progress from streamable handles */
struct FLyraAssetManagerStartupJob
{
	// FStreamableHandle: A handle to a synchronous or async load. As long as the handle is Active, loaded assets will stay in memory
	TFunction<void(const FLyraAssetManagerStartupJob&, TSharedPtr<FStreamableHandle>&)> JobFunc;
	FString JobName;
	float JobWeight;

	/** Simple job that is all synchronous */
	FLyraAssetManagerStartupJob(const FString& InJobName, const TFunction<void(const FLyraAssetManagerStartupJob&, TSharedPtr<FStreamableHandle>&)>& InJobFunc, float InJobWeight)
		: JobFunc(JobFunc),
		JobName(InJobName),
		JobWeight(InJobWeight)
	{

	}

	/** Perform actual loading, will return a handle if it created one */
	TSharedPtr<FStreamableHandle> DoJob() const;
};