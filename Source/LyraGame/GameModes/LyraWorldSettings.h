// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/WorldSettings.h"
#include "LyraWorldSettings.generated.h"

class ULyraExperienceDefinition;

/**
 *
 */
UCLASS()
class LYRAGAME_API ALyraWorldSettings : public AWorldSettings
{
	GENERATED_BODY()

public:

	ALyraWorldSettings(const FObjectInitializer& ObjectInitializer);

	// 返回服务器打开这个地图时使用的默认体验
	FPrimaryAssetId GetDefaultGameplayExperience() const;

protected:
	// 服务器打开这个地图时使用的默认体验
	UPROPERTY(EditDefaultsOnly, Category = GameMode)
		TSoftClassPtr<ULyraExperienceDefinition> DefaultGameplayExperience;
};
