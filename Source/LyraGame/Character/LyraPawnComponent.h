// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/PawnComponent.h"
#include "LyraPawnComponent.generated.h"

/**
 *
 */
UCLASS(Blueprintable, meta = (BlueprintSpawnableComponent))
class LYRAGAME_API ULyraPawnComponent : public UPawnComponent
{
	GENERATED_BODY()

public:
	ULyraPawnComponent(const FObjectInitializer& ObjectInitializer);
};
