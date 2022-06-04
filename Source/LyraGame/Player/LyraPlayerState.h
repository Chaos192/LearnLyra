// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ModularPlayerState.h"
#include "AbilitySystemInterface.h"
#include "LyraPlayerState.generated.h"

class ULyraAbilitySystemComponent;
class UAbilitySystemComponent;
class ULyraExperienceDefinition;
class ULyraPawnData;

/**
 *
 */
UCLASS()
class LYRAGAME_API ALyraPlayerState : public AModularPlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	ALyraPlayerState(const FObjectInitializer& ObjectInitializer);

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION(BlueprintCallable)
		ULyraAbilitySystemComponent* GetLyraAbilitySystemComponent() const;
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	template<class T>
	const T* GetPawnData() const { return Cast<T>(PawnData); }

	void SetPawnData(const ULyraPawnData* InPawnData);

	virtual void PreInitializeComponents() override;
	virtual void PostInitializeComponents() override;

protected:
	UFUNCTION()
		void OnRep_PawnData();

	UPROPERTY(ReplicatedUsing = OnRep_PawnData)
		const ULyraPawnData* PawnData;

private:
	UPROPERTY(VisibleAnywhere)
		ULyraAbilitySystemComponent* AbilitySystemComponent;

	void OnExperienceLoaded(const ULyraExperienceDefinition* CurrentExperience);
};
