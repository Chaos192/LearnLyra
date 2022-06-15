// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "LyraInputComponent.generated.h"

/**
 * 配置 UInputSettings::DefaultInputComponentClass
 * 在 APlayerController::SetupInputComponent() 中创建
 */
UCLASS()
class LYRAGAME_API ULyraInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()

public:

	ULyraInputComponent(const FObjectInitializer& ObjectInitializer);
};
