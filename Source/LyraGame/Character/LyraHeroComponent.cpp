#include "Character/LyraHeroComponent.h"
#include "LyraLogChannels.h"
#include "Character/LyraPawnExtensionComponent.h"
#include "Player/LyraPlayerState.h"
#include "Character/LyraPawnData.h"
#include "Player/LyraPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "Input/LyraInputConfig.h"
#include "LyraGameplayTags.h"
#include "Input/LyraInputComponent.h"
#include "Character/LyraCharacter.h"

ULyraHeroComponent::ULyraHeroComponent(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	bPawnHasInitialized = false;
}

void ULyraHeroComponent::OnRegister()
{
	Super::OnRegister();

	if (const APawn* Pawn = GetPawn<APawn>())
	{
		if (ULyraPawnExtensionComponent* PawnExtComp = ULyraPawnExtensionComponent::FindPawnExtensionComponent(Pawn))
		{
			PawnExtComp->OnPawnReadyToInitialize_RegisterAndCall(
				FSimpleMulticastDelegate::FDelegate::CreateUObject(
					this,
					&ThisClass::OnPawnReadyToInitialize
				));
		}
	}
	else
	{
		UE_LOG(LogLyra, Error, TEXT("[ULyraHeroComponent::OnRegister] This component has been added to a blueprint whose base class is not a Pawn. To use this component, it MUST be placed on a Pawn Blueprint."));
	}
}

void ULyraHeroComponent::OnPawnReadyToInitialize()
{
	if (!ensure(!bPawnHasInitialized))
	{
		return;
	}

	APawn* Pawn = GetPawn<APawn>();
	if (!Pawn)
	{
		return;
	}

	const bool bIsLocallyControlled = Pawn->IsLocallyControlled();

	ALyraPlayerState* LyraPS = GetPlayerState<ALyraPlayerState>();
	check(LyraPS);

	const ULyraPawnData* PawnData = nullptr;

	if (ULyraPawnExtensionComponent* PawnExtComp = ULyraPawnExtensionComponent::FindPawnExtensionComponent(Pawn))
	{
		PawnData = PawnExtComp->GetPawnData<ULyraPawnData>();

		// TODO: sola 初始化ASC
	}

	if (ALyraPlayerController* LyraPC = GetController<ALyraPlayerController>())
	{
		if (Pawn->InputComponent != nullptr)
		{
			InitializePlayerInput(Pawn->InputComponent);
		}
	}

	bPawnHasInitialized = true;
}

void ULyraHeroComponent::InitializePlayerInput(UInputComponent* PlayerInputComponent)
{
	check(PlayerInputComponent);

	const APawn* Pawn = GetPawn<APawn>();
	if (!Pawn)
	{
		return;
	}

	const APlayerController* PC = GetController<APlayerController>();
	check(PC);

	const ULocalPlayer* LP = PC->GetLocalPlayer();
	check(LP);

	UEnhancedInputLocalPlayerSubsystem* Subsystem = LP->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
	check(Subsystem);

	Subsystem->ClearAllMappings();

	if (const ULyraPawnExtensionComponent* PawnExtComp = ULyraPawnExtensionComponent::FindPawnExtensionComponent(Pawn))
	{
		// PawnData: HeroData_ShooterGame
		if (const ULyraPawnData* PawnData = PawnExtComp->GetPawnData<ULyraPawnData>())
		{
			// InputConfig: InputData_Hero,配置InputAction到GameplayTag的映射
			if (const ULyraInputConfig* InputConfig = PawnData->InputConfig)
			{
				const FLyraGameplayTags& GameplayTags = FLyraGameplayTags::Get();

				ULyraInputComponent* LyraIC = CastChecked<ULyraInputComponent>(PlayerInputComponent);
				// 应用ULyraSettingsLocal::RegisteredInputConfigs中储存的FKey到InputAction的映射
				// 配置在 IMC_Default_KBM
				LyraIC->AddInputMappings(InputConfig, Subsystem);

				// ULyraSettingsLocal代理,暂不处理

				// 根据GameplayTag,找到InputData_Hero中配置的InputAction
				// 然后将InputAction绑定到回调函数
				// 这里其实是将GameplayTag到回调函数的映射写死
				LyraIC->BindNativeAction(InputConfig, GameplayTags.InputTag_Move, ETriggerEvent::Triggered, this, &ThisClass::Input_Move, false);
				LyraIC->BindNativeAction(InputConfig, GameplayTags.InputTag_Look_Mouse, ETriggerEvent::Triggered, this, &ThisClass::Input_LookMouse, false);
				LyraIC->BindNativeAction(InputConfig, GameplayTags.InputTag_Crouch, ETriggerEvent::Triggered, this, &ThisClass::Input_Crouch, false);
			}
		}
	}

	if (ensure(!bReadyToBindInputs))
	{
		bReadyToBindInputs = true;
	}

	// UGameFrameworkComponentManager::SendGameFrameworkComponentExtensionEvent, 暂不处理
}

void ULyraHeroComponent::Input_Move(const FInputActionValue& InputActionValue)
{
	APawn* Pawn = GetPawn<APawn>();
	AController* Controller = Pawn ? Pawn->GetController() : nullptr;

	if (Controller)
	{
		const FVector2D Value = InputActionValue.Get<FVector2D>();
		const FRotator MovementRotation(0.0f, Controller->GetControlRotation().Yaw, 0.0f);

		if (Value.X != 0.0f)
		{
			const FVector MovementDirection = MovementRotation.RotateVector(FVector::RightVector);
			Pawn->AddMovementInput(MovementDirection, Value.X);
		}

		if (Value.Y != 0.0f)
		{
			const FVector MovementDirection = MovementRotation.RotateVector(FVector::ForwardVector);
			Pawn->AddMovementInput(MovementDirection, Value.Y);
		}
	}
}

void ULyraHeroComponent::Input_LookMouse(const FInputActionValue& InputActionValue)
{
	APawn* Pawn = GetPawn<APawn>();

	if (!Pawn)
	{
		return;
	}

	const FVector2D Value = InputActionValue.Get<FVector2D>();

	if (Value.X != 0.0f)
	{
		Pawn->AddControllerYawInput(Value.X);
	}

	if (Value.Y != 0.0f)
	{
		Pawn->AddControllerPitchInput(Value.Y * -1.0f);
	}
}

void ULyraHeroComponent::Input_Crouch(const FInputActionValue& InputActionValue)
{
	if (ALyraCharacter* Character = GetPawn<ALyraCharacter>())
	{
		Character->ToggleCrouch();
	}
}
