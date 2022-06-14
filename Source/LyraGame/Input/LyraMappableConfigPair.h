#pragma once

#include "CoreMinimal.h"
#include "LyraMappableConfigPair.generated.h"

/** A container to organize potentially unloaded player mappable configs to their CommonUI input type */
USTRUCT()
struct FMappableConfigPair
{
	GENERATED_BODY()

public:

	/** 注册配置中的映射 */
	static bool RegisterPair(const FMappableConfigPair& Pair);
};