// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "LyraPawnData.generated.h"

/**
 *
 */
UCLASS(BlueprintType, Const, Meta = (DisplayName = "Lyra Pawn Data", ShortTooltip = "Data asset used to define a Pawn."))
class LYRAGAME_API ULyraPawnData : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:

	ULyraPawnData(const FObjectInitializer& ObjectInitializer);

	// 用于实例化Pawn的Class,应该继承ALyraCharacter
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Lyra|Pawn")
		TSubclassOf<APawn> PawnClass;
};
