#include "Character/LyraPawnExtensionComponent.h"
#include "Net/UnrealNetwork.h"
#include "LyraLogChannels.h"
#include "Character/LyraPawnData.h"
#include "AbilitySystem/LyraAbilitySystemComponent.h"

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

void ULyraPawnExtensionComponent::InitializeAbilitySystem(ULyraAbilitySystemComponent* InASC, AActor* InOwnerActor)
{
	check(InASC);
	check(InOwnerActor);

	if (AbilitySystemComponent == InASC)
	{
		return;
	}

	if (AbilitySystemComponent)
	{
		// 暂不处理清理旧的ASC
	}

	APawn* Pawn = GetPawnChecked<APawn>();
	AActor* ExistingAvatar = InASC->GetAvatarActor();

	UE_LOG(LogLyra, Verbose, TEXT("Setting up ASC [%s] on pawn [%s] owner [%s], existing [%s] "), *GetNameSafe(InASC), *GetNameSafe(Pawn), *GetNameSafe(InOwnerActor), *GetNameSafe(ExistingAvatar));

	if ((ExistingAvatar != nullptr) && (ExistingAvatar != Pawn))
	{
		UE_LOG(LogLyra, Log, TEXT("Existing avatar (authority=%d)"), ExistingAvatar->HasAuthority() ? 1 : 0);

		// 暂不处理
	}

	AbilitySystemComponent = InASC;
	AbilitySystemComponent->InitAbilityActorInfo(InOwnerActor, Pawn);

	if (ensure(PawnData))
	{
		// TODO: sola 处理Tag,主要是技能打断,可能会影响当前逻辑
	}

	OnAbilitySystemInitialized.Broadcast();
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
	if (!OnAbilitySystemInitialized.IsBoundToObject(Delegate.GetUObject()))
	{
		OnAbilitySystemInitialized.Add(Delegate);
	}

	if (AbilitySystemComponent)
	{
		Delegate.Execute();
	}
}

void ULyraPawnExtensionComponent::OnRep_PawnData()
{
	CheckPawnReadyToInitialize();
}
