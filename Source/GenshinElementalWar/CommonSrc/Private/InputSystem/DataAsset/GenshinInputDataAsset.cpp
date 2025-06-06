// Copyright © 2025 鸿源z 保留所有权利


#include "GenshinElementalWar/CommonSrc/Public/InputSystem/DataAsset/GenshinInputDataAsset.h"

const UInputAction* UGenshinInputDataAsset::GetInputActionFromTag(const FGameplayTag& InputTag) const
{
	for (FGenshinInputAction AbilityInputAction : AbilityInputActions)
	{
		if (AbilityInputAction.InputTag == InputTag)
		{
			return AbilityInputAction.InputAction;
		}
	}
	return nullptr;
}

FGameplayTag UGenshinInputDataAsset::GetInputTagFromAction(const UInputAction* InputAction) const
{
	for (FGenshinInputAction AbilityInputAction : AbilityInputActions)
	{
		if (AbilityInputAction.InputAction == InputAction)
		{
			return AbilityInputAction.InputTag;
		}
	}
	return FGameplayTag();
}
