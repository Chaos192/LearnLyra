#pragma once

#include "CoreMinimal.h"
#include "Character/LyraPawnComponent.h"
#include "LyraPawnExtensionComponent.generated.h"

class ULyraPawnData;
class ULyraAbilitySystemComponent;

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

	// 如果指定的Actor存在pawn extension component,则返回
	UFUNCTION(BlueprintPure, Category = "Lyra|Pawn")
		static ULyraPawnExtensionComponent* FindPawnExtensionComponent(const AActor* Actor);

	template<class T>
	const T* GetPawnData() const { return Cast<T>(PawnData); }

	void SetPawnData(const ULyraPawnData* InPawnData);

	UFUNCTION(BlueprintPure, Category = "Lyra|Pawn")
		ULyraAbilitySystemComponent* GetLyraAbilitySystemComponent() const
	{
		return AbilitySystemComponent;
	}

	// 当Pawn变成ASC的Avatar时,由Pawn调用
	void InitializeAbilitySystem(ULyraAbilitySystemComponent* InASC, AActor* InOwnerActor);

	// ALyraCharacter::SetupPlayerInputComponent()调用
	void SetupPlayerInputComponent();

	// 在Pawn需要检测它是否准备好初始化,的任意时刻都调用此函数,(pawn data设置成功, possessed, 等等)
	bool CheckPawnReadyToInitialize();

	// 注册OnPawnReadyToInitialize代理,如果条件已经满足就广播
	void OnPawnReadyToInitialize_RegisterAndCall(FSimpleMulticastDelegate::FDelegate Delegate);

	// 注册OnAbilitySystemInitialized代理,如果条件已经满足就广播
	void OnAbilitySystemInitialized_RegisterAndCall(FSimpleMulticastDelegate::FDelegate Delegate);

protected:

	// pawn拥有初始化所需的所有数据时,广播的代理
	FSimpleMulticastDelegate OnPawnReadyToInitialize;

	// 当Pawn成为Avatar Actor时广播此代理
	FSimpleMulticastDelegate OnAbilitySystemInitialized;

	// 用于 Spawn Pawn 的数据
	UPROPERTY(EditInstanceOnly, ReplicatedUsing = OnRep_PawnData, Category = "Lyra|Pawn")
		const ULyraPawnData* PawnData;

	UFUNCTION()
		void OnRep_PawnData();

	// 缓存ASC方便使用
	UPROPERTY()
		ULyraAbilitySystemComponent* AbilitySystemComponent;

	// pawn拥有初始化所需的所有数据时为true
	int32 bPawnReadyToInitialize : 1;
};
