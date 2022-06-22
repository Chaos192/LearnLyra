#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"

#include "LyraGameplayAbility.generated.h"

class ULyraAbilitySystemComponent;
class ALyraCharacter;
class ALyraPlayerController;
class AController;
class ULyraHeroComponent;

/**
 * 定义GA如何激活
 */
UENUM(BlueprintType)
enum class ELyraAbilityActivationPolicy : uint8
{
	// 按下按键时激活
	OnInputTriggered,

	// 按住按键时不断激活
	WhileInputActive,

	// 设置Avatar时激活
	OnSpawn
};

UCLASS(Abstract, hideCategories = Input, meta = (ShortToolTip = "此项目的Gameplay Ability基类"))
class ULyraGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

public:

	friend class ULyraAbilitySystemComponent;

	ULyraGameplayAbility(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable, Category = "Lyra|Ability")
		ULyraAbilitySystemComponent* GetLyraAbilitySystemComponentFromActorInfo() const;

	UFUNCTION(BlueprintCallable, Category = "Lyra|Ability")
		ALyraPlayerController* GetLyraPlayerControllerFromActorInfo() const;

	UFUNCTION(BlueprintCallable, Category = "Lyra|Ability")
		AController* GetControllerFromActorInfo() const;

	UFUNCTION(BlueprintCallable, Category = "Lyra|Ability")
		ALyraCharacter* GetLyraCharacterFromActorInfo() const;

	UFUNCTION(BlueprintCallable, Category = "Lyra|Ability")
		ULyraHeroComponent* GetHeroComponentFromActorInfo() const;

	ELyraAbilityActivationPolicy GetActivationPolicy() const
	{
		return ActivationPolicy;
	}

protected:

	//~UGameplayAbility interface
	virtual bool CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags /* = nullptr */, const FGameplayTagContainer* TargetTags /* = nullptr */, OUT FGameplayTagContainer* OptionalRelevantTags /* = nullptr */) const override;
	virtual void OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
	//~End of UGameplayAbility interface

	// 这个GA被赋予ASC时调用
	UFUNCTION(BlueprintImplementableEvent, Category = Ability, DisplayName = "OnAbilityAdded")
		void K2_OnAbilityAdded();

protected:

	// 定义GA如何激活
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Lyra|Ability Activation")
		ELyraAbilityActivationPolicy ActivationPolicy;
};