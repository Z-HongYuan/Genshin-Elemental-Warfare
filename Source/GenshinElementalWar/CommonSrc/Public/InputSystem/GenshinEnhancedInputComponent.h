// Copyright © 2025 鸿源z 保留所有权利

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "DataAsset/GenshinInputDataAsset.h"
#include "GenshinEnhancedInputComponent.generated.h"

/**
 * 使用模版绑定输入的回调函数
 */
UCLASS()
class GENSHINELEMENTALWAR_API UGenshinEnhancedInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()
	
public:
	template <class UserClass, typename PressedFuncType,typename ReleasedFuncType, typename HeldFuncType>
	void BindAbilityAction(const UGenshinInputDataAsset* InputDataAsset, UserClass* Object, PressedFuncType PressedFunc ,
		ReleasedFuncType ReleasedFunc, HeldFuncType HeldFunc);
};

//模版函数
template <class UserClass, typename PressedFuncType, typename ReleasedFuncType, typename HeldFuncType>
void UGenshinEnhancedInputComponent::BindAbilityAction(const UGenshinInputDataAsset* InputDataAsset, UserClass* Object,
	PressedFuncType PressedFunc, ReleasedFuncType ReleasedFunc, HeldFuncType HeldFunc)
{
	check(InputDataAsset);
	for (const FGenshinInputAction& ActionData : InputDataAsset->AbilityInputActions)
	{
		if (ActionData.InputAction && ActionData.InputTag.IsValid())
		{
			if (HeldFunc)
			{
				BindAction(ActionData.InputAction, ETriggerEvent::Triggered, Object, HeldFunc, ActionData.InputTag);
			}
			if (ReleasedFunc)
			{
				BindAction(ActionData.InputAction, ETriggerEvent::Completed, Object, ReleasedFunc, ActionData.InputTag);
			}
			if (PressedFunc)
			{
				BindAction(ActionData.InputAction, ETriggerEvent::Started, Object, PressedFunc, ActionData.InputTag);
			}
		}
	}
}
