// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "LyraExperienceDefinition.generated.h"

class ULyraPawnData;

/**
 *
 */
UCLASS()
class LYRAGAME_API ULyraExperienceDefinition : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	ULyraExperienceDefinition();

	UPROPERTY(EditDefaultsOnly, Category = Gameplay)
		TObjectPtr<const ULyraPawnData> DefaultPawnData;
};
