#pragma once

#include "CoreMinimal.h"
#include "Character/LyraPawnComponent.h"
#include "LyraPawnExtensionComponent.generated.h"

class ULyraPawnData;

/**
 * ALyraCharacter构造函数中生成
 */
UCLASS()
class LYRAGAME_API ULyraPawnExtensionComponent : public ULyraPawnComponent
{
	GENERATED_BODY()

public:

	ULyraPawnExtensionComponent(const FObjectInitializer& ObjectInitializer);

	virtual void GetLifetimeReplicatedProps(TArray< class FLifetimeProperty >& OutLifetimeProps) const override;

	// Returns the pawn extension component if one exists on the specified actor.
	UFUNCTION(BlueprintPure, Category = "Lyra|Pawn")
		static ULyraPawnExtensionComponent* FindPawnExtensionComponent(const AActor* Actor);

	template<class T>
	const T* GetPawnData() const { return Cast<T>(PawnData); }

	void SetPawnData(const ULyraPawnData* InPawnData);

	// ALyraCharacter::SetupPlayerInputComponent()调用
	void SetupPlayerInputComponent();

	// Call this anytime the pawn needs to check if it's ready to be initialized (pawn data assigned, possessed, etc..). 
	bool CheckPawnReadyToInitialize();

	// Register with the OnPawnReadyToInitialize delegate and broadcast if condition is already met.
	void OnPawnReadyToInitialize_RegisterAndCall(FSimpleMulticastDelegate::FDelegate Delegate);

protected:

	// Delegate fired when pawn has everything needed for initialization.
	FSimpleMulticastDelegate OnPawnReadyToInitialize;

	// Pawn data used to create the pawn.  Specified from a spawn function or on a placed instance.
	UPROPERTY(EditInstanceOnly, ReplicatedUsing = OnRep_PawnData, Category = "Lyra|Pawn")
		const ULyraPawnData* PawnData;

	UFUNCTION()
		void OnRep_PawnData();

	// True when the pawn has everything needed for initialization.
	int32 bPawnReadyToInitialize : 1;
};
