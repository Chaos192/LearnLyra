#pragma once

#include "CoreMinimal.h"
#include "LyraGameplayAbility.h"
#include "LyraGameplayAbility_Jump.generated.h"

UCLASS(Abstract)
class ULyraGameplayAbility_Jump : public ULyraGameplayAbility
{
	GENERATED_BODY()

public:

	ULyraGameplayAbility_Jump(const FObjectInitializer& ObjectInitializer);

};