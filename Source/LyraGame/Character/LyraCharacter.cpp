#include "Character/LyraCharacter.h"
#include "Character/LyraPawnExtensionComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

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

void ALyraCharacter::ToggleCrouch()
{
	// TODO: sola 和移动组件关联
	const UCharacterMovementComponent* LyraMoveComp = GetCharacterMovement();

	if (bIsCrouched || LyraMoveComp->bWantsToCrouch)
	{
		UnCrouch();
	}
	else
	{
		Crouch();
	}
}
