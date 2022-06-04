// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ModularGameMode.h"
#include "LyraGameMode.generated.h"

class ULyraPawnData;
class ULyraExperienceDefinition;

/**
 *
 */
UCLASS()
class LYRAGAME_API ALyraGameMode : public AModularGameModeBase
{
	GENERATED_BODY()

public:

	ALyraGameMode(const FObjectInitializer& ObjectInitializer);

	const ULyraPawnData* GetPawnDataForController(const AController* InController) const;
};
