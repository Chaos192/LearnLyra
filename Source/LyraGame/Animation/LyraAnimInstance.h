#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "GameplayEffectTypes.h"

#include "LyraAnimInstance.generated.h"

class UAbilitySystemComponent;

UCLASS(config = Game)
class ULyraAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:

	ULyraAnimInstance(const FObjectInitializer& ObjectInitialize);

	virtual void InitializeWithAbilitySystem(UAbilitySystemComponent* ASC);

protected:

	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

protected:

	// 可以被映射到蓝图变量的Tags,这些变量会随着Tag的增删自动更新
	// 应使用此变量代替手动查询Tag
	UPROPERTY(EditDefaultsOnly, Category = "GameplayTags")
		FGameplayTagBlueprintPropertyMap GameplayTagPropertyMap;

	UPROPERTY(BlueprintReadOnly, Category = "Character State Data")
		float GroundDistance = -1.0f;
};