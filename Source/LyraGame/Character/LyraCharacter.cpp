#include "Character/LyraCharacter.h"
#include "Character/LyraPawnExtensionComponent.h"

ALyraCharacter::ALyraCharacter(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	PawnExtComponent = CreateDefaultSubobject<ULyraPawnExtensionComponent>(TEXT("PawnExtensionComponent"));
	// TODO: sola 注册技能代理
}

void ALyraCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PawnExtComponent->SetupPlayerInputComponent();
}
