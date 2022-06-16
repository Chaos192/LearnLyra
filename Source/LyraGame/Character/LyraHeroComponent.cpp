#include "Character/LyraHeroComponent.h"
#include "LyraLogChannels.h"
#include "Character/LyraPawnExtensionComponent.h"
#include "Player/LyraPlayerState.h"
#include "Character/LyraPawnData.h"
#include "Player/LyraPlayerController.h"

ULyraHeroComponent::ULyraHeroComponent(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{

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
	// TODO: sola 从这里开始
}
