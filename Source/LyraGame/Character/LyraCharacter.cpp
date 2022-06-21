#include "Character/LyraCharacter.h"
#include "Character/LyraPawnExtensionComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "AbilitySystem/LyraAbilitySystemComponent.h"

ALyraCharacter::ALyraCharacter(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	PawnExtComponent = CreateDefaultSubobject<ULyraPawnExtensionComponent>(TEXT("PawnExtensionComponent"));
	PawnExtComponent->OnAbilitySystemInitialized_RegisterAndCall(
		FSimpleMulticastDelegate::FDelegate::CreateUObject(
			this,
			&ThisClass::OnAbilitySystemInitialized
		));
}

ULyraAbilitySystemComponent* ALyraCharacter::GetLyraAbilitySystemComponent()
{
	return Cast<ULyraAbilitySystemComponent>(GetAbilitySystemComponent());
}

UAbilitySystemComponent* ALyraCharacter::GetAbilitySystemComponent() const
{
	return PawnExtComponent->GetLyraAbilitySystemComponent();
}

void ALyraCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PawnExtComponent->SetupPlayerInputComponent();
}

void ALyraCharacter::OnAbilitySystemInitialized()
{
	ULyraAbilitySystemComponent* LyraASC = GetLyraAbilitySystemComponent();
	check(LyraASC);

	// TODO: sola 暂不处理血量和Tag
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
