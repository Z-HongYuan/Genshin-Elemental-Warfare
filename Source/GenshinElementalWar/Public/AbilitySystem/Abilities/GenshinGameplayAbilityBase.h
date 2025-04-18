// Copyright © 2025 鸿源z 保留所有权利

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "GenshinGameplayAbilityBase.generated.h"

/**
 * 带有InputTag识别输入
 */
UCLASS()
class GENSHINELEMENTALWAR_API UGenshinGameplayAbilityBase : public UGameplayAbility
{
	GENERATED_BODY()

public:
	UGenshinGameplayAbilityBase();
	
	//InputTag,用于判断输入
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "0_InputTag")
	FGameplayTag InputTag;

	//输入释放操作,从ASC触发
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "OnInputReleased"), Category = "Ability")
	void K2_OnInputReleased();

protected:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;

	virtual void InputPressed(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo) override;

	virtual void InputReleased(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo) override;
};

