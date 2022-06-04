// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModes/LyraGameState.h"
#include "GameModes/LyraExperienceManagerComponent.h"
#include "AbilitySystem/LyraAbilitySystemComponent.h"

ALyraGameState::ALyraGameState(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	AbilitySystemComponent = ObjectInitializer.CreateDefaultSubobject<ULyraAbilitySystemComponent>(this, TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	ExperienceManagerComponent = CreateDefaultSubobject<ULyraExperienceManagerComponent>(TEXT("ExperienceManagerComponent"));
}

UAbilitySystemComponent* ALyraGameState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}
