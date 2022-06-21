// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonPlayerController.h"
#include "LyraPlayerController.generated.h"

class ALyraPlayerState;
class ULyraAbilitySystemComponent;

/**
 *
 */
UCLASS()
class LYRAGAME_API ALyraPlayerController : public ACommonPlayerController
{
	GENERATED_BODY()

public:

	ALyraPlayerController(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable, Category = "Lyra|PlayerController")
		ALyraPlayerState* GetLyraPlayerState() const;

	UFUNCTION(BlueprintCallable, Category = "Lyra|PlayerController")
		ULyraAbilitySystemComponent* GetLyraAbilitySystemComponent() const;

protected:

	//~APlayerController interface
	virtual void PostProcessInput(const float DeltaTime, const bool bGamePaused) override;
	//~End of APlayerController interface
};
