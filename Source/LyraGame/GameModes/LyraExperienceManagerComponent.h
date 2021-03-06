// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/GameStateComponent.h"
#include "GameFeaturePluginOperationResult.h"
#include "LyraExperienceManagerComponent.generated.h"

class ULyraExperienceDefinition;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnLyraExperienceLoaded, const ULyraExperienceDefinition*);

enum class ELyraExperienceLoadState
{
	UnLoaded,
	Loading,
	LoadingGameFeatures,
	Loaded,
};

/**
 *
 */
UCLASS()
class LYRAGAME_API ULyraExperienceManagerComponent : public UGameStateComponent
{
	GENERATED_BODY()

public:

	ULyraExperienceManagerComponent(const FObjectInitializer& ObjectInitializer);

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	void ServerSetCurrentExperience(FPrimaryAssetId ExperienceId);

	// 一旦体验被加载,确保代理被调用
	// 如果体验已经加载,立即调用代理
	// &&右值引用
	void CallOrRegister_OnExperienceLoaded(FOnLyraExperienceLoaded::FDelegate&& Delegate);

	// 返回体验是否已完全加载
	bool IsExperienceLoaded() const;

	const ULyraExperienceDefinition* GetCurrentExperienceChecked() const;

private:
	UFUNCTION()
		void OnRep_CurrentExperience();

	void StartExperienceLoad();
	void OnExperienceLoadComplete();
	void OnGameFeaturePluginLoadComplete(const UE::GameFeatures::FResult& Result);
	void OnExperienceFullLoadCompleted();

	UPROPERTY(ReplicatedUsing = OnRep_CurrentExperience)
		const ULyraExperienceDefinition* CurrentExperience;

	ELyraExperienceLoadState LoadState = ELyraExperienceLoadState::UnLoaded;

	int32 NumGameFeaturePluginsLoading = 0;
	TArray<FString> GameFeaturePluginURLs;

	// 体验完成加载后调用的代理
	FOnLyraExperienceLoaded OnExperienceLoaded;
	FOnLyraExperienceLoaded OnExperienceLoaded_LowPriority;
};
