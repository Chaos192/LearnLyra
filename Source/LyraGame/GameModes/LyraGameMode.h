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

	// ~AGameModeBase interface
	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;
	virtual UClass* GetDefaultPawnClassForController_Implementation(AController* InController) override;
	// Spawn Pawn的直接函数
	virtual APawn* SpawnDefaultPawnAtTransform_Implementation(AController* NewPlayer, const FTransform& SpawnTransform) override;
	virtual void HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer) override;
	// 创建GameState
	virtual void InitGameState() override;
	// ~End of AGameModeBase interface

protected:

	void OnExperienceLoaded(const ULyraExperienceDefinition* CurrentExperience);
	bool IsExperienceLoaded() const;

	void OnMatchAssignmentGiven(FPrimaryAssetId ExperienceId, const FString& ExperienceIdSource);

	// InitGame()设置定时器下一帧调用,确保体验加载完成的代理已绑定
	// 从配置中获取体验
	void HandleMatchAssigmentIfNotExpectingOne();
};
