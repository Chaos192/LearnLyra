#include "Character/LyraPawnExtensionComponent.h"
#include "Net/UnrealNetwork.h"
#include "LyraLogChannels.h"
#include "Character/LyraPawnData.h"

ULyraPawnExtensionComponent::ULyraPawnExtensionComponent(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	PrimaryComponentTick.bStartWithTickEnabled = false;
	PrimaryComponentTick.bCanEverTick = false;

	SetIsReplicatedByDefault(true);

	PawnData = nullptr;
	bPawnReadyToInitialize = false;
}

void ULyraPawnExtensionComponent::GetLifetimeReplicatedProps(TArray< class FLifetimeProperty >& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ULyraPawnExtensionComponent, PawnData);
}

ULyraPawnExtensionComponent* ULyraPawnExtensionComponent::FindPawnExtensionComponent(const AActor* Actor)
{
	return Actor ? Actor->FindComponentByClass<ULyraPawnExtensionComponent>() : nullptr;
}

void ULyraPawnExtensionComponent::SetPawnData(const ULyraPawnData* InPawnData)
{
	check(InPawnData);

	bPawnReadyToInitialize = false;

	APawn* Pawn = GetPawnChecked<APawn>();

	if (Pawn->GetLocalRole() != ROLE_Authority)
	{
		return;
	}

	if (PawnData)
	{
		UE_LOG(LogLyra, Error, TEXT("Trying to set PawnData [%s] on pawn [%s] that already has valid PawnData [%s]."), *GetNameSafe(InPawnData), *GetNameSafe(Pawn), *GetNameSafe(PawnData));
		return;
	}

	PawnData = InPawnData;

	Pawn->ForceNetUpdate();

	CheckPawnReadyToInitialize();
}

void ULyraPawnExtensionComponent::SetupPlayerInputComponent()
{
	CheckPawnReadyToInitialize();
}

bool ULyraPawnExtensionComponent::CheckPawnReadyToInitialize()
{
	if (bPawnReadyToInitialize)
	{
		return true;
	}

	if (!PawnData)
	{
		return false;
	}

	APawn* Pawn = GetPawnChecked<APawn>();

	const bool bHasAuthority = Pawn->HasAuthority();
	const bool bIsLocallyControlled = Pawn->IsLocallyControlled();

	if (bHasAuthority || bIsLocallyControlled)
	{
		if (!GetController<AController>())
		{
			return false;
		}
	}

	// 遍历ULyraReadyInterface,暂不处理

	bPawnReadyToInitialize = true;
	OnPawnReadyToInitialize.Broadcast();

	return true;
}

void ULyraPawnExtensionComponent::OnPawnReadyToInitialize_RegisterAndCall(FSimpleMulticastDelegate::FDelegate Delegate)
{
	if (!OnPawnReadyToInitialize.IsBoundToObject(Delegate.GetUObject()))
	{
		OnPawnReadyToInitialize.Add(Delegate);
	}

	if (bPawnReadyToInitialize)
	{
		Delegate.Execute();
	}
}

void ULyraPawnExtensionComponent::OnAbilitySystemInitialized_RegisterAndCall(FSimpleMulticastDelegate::FDelegate Delegate)
{

}

void ULyraPawnExtensionComponent::OnRep_PawnData()
{
	CheckPawnReadyToInitialize();
}
