// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "LyraExperienceDefinition.generated.h"

class ULyraPawnData;

/**
 *
 */
UCLASS(BlueprintType, Const)
class LYRAGAME_API ULyraExperienceDefinition : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	ULyraExperienceDefinition();

	// 这个体验想要激活的GameFeature插件列表
	UPROPERTY(EditDefaultsOnly, Category = Gameplay)
		TArray<FString> GameFeaturesToEnable;

	UPROPERTY(EditDefaultsOnly, Category = Gameplay)
		TObjectPtr<const ULyraPawnData> DefaultPawnData;
};
