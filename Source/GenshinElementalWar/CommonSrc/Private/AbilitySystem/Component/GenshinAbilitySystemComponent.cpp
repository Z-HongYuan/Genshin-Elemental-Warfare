// Copyright © 2025 鸿源z 保留所有权利


#include "GenshinElementalWar/CommonSrc/Public/AbilitySystem/Component/GenshinAbilitySystemComponent.h"

#include "AbilitySystemLog.h"

UGenshinAbilitySystemComponent::UGenshinAbilitySystemComponent()
{
	// SetIsReplicated(true); //选择设置是否复制
}

//包装GiveAbility(),使其在Give的时候添加InputTag
FGameplayAbilitySpecHandle UGenshinAbilitySystemComponent::GiveAbilityWithTag(FGameplayAbilitySpec& Spec)
{
	if (const UGenshinGameplayAbilityBase* GenshinAbility = Cast<UGenshinGameplayAbilityBase>(Spec.Ability))
	{
		if (GenshinAbility->InputTag.IsValid())
		{
			Spec.GetDynamicSpecSourceTags().AddTag(GenshinAbility->InputTag);
		}
	}
	return GiveAbility(Spec);
}

FGameplayAbilitySpecHandle UGenshinAbilitySystemComponent::K2_GiveAbilityWithTag(TSubclassOf<UGameplayAbility> AbilityClass, int32 Level, int32 InputID)
{
	// build and validate the ability spec
	FGameplayAbilitySpec AbilitySpec = BuildAbilitySpecFromClass(AbilityClass, Level, InputID);

	// validate the class
	if (!IsValid(AbilitySpec.Ability))
	{
		ABILITY_LOG(Error, TEXT("K2_GiveAbility() called with an invalid Ability Class."));

		return FGameplayAbilitySpecHandle();
	}

	// grant the ability and return the handle. This will run validation and authority checks
	return GiveAbilityWithTag(AbilitySpec);
}

void UGenshinAbilitySystemComponent::AbilityInputTagHeld(const FGameplayTag& InputTag)
{
	if (!InputTag.IsValid()) return;

	for (FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())	//循环查找并激活包含有对应InputTag的Ability
	{
		if (AbilitySpec.GetDynamicSpecSourceTags().HasTagExact(InputTag))
		{
			AbilitySpecInputPressed(AbilitySpec);	//通知Ability内的输入按下
			if (!AbilitySpec.IsActive())
			{
				TryActivateAbility(AbilitySpec.Handle);	//并且如果能力未被激活,就激活一次
			}
		}
	}
}

void UGenshinAbilitySystemComponent::AbilityInputTagReleased(const FGameplayTag& InputTag)
{
	if (!InputTag.IsValid()) return;

	for (FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())	//循环查找并激活包含有对应InputTag的Ability
	{
		if (AbilitySpec.GetDynamicSpecSourceTags().HasTagExact(InputTag))
		{
			AbilitySpecInputReleased(AbilitySpec);	//通知Ability内的输入释放
		}
	}
}
