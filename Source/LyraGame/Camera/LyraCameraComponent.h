#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"

#include "LyraCameraComponent.generated.h"

UCLASS()
class ULyraCameraComponent : public UCameraComponent
{
	GENERATED_BODY()

public:

	ULyraCameraComponent(const FObjectInitializer& ObjectInitializer);
};