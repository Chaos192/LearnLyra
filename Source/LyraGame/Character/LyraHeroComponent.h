// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/LyraPawnComponent.h"
#include "LyraHeroComponent.generated.h"

/**
 *
 */
UCLASS(Blueprintable, meta = (BlueprintSpawnableComponent))
class LYRAGAME_API ULyraHeroComponent : public ULyraPawnComponent
{
	GENERATED_BODY()

public:
	ULyraHeroComponent(const FObjectInitializer& ObjectInitializer);
};
