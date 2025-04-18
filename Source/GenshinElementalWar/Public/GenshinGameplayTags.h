// Copyright © 2025 鸿源z 保留所有权利

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"

/**
 * GenshinGameplayTags
 * 单例,全局唯一
 * 在Cpp中的所有游戏标签都应该在这里注册
 * 包含原生GameplayTags
 */

struct FGenshinGameplayTags
{
public:
	static const FGenshinGameplayTags& Get() {return GameplayTags;}
	static void InitializeNativeGameplayTags();

	//添加Tag
	FGameplayTag Tag_GameplayAbility_ActivateFail_IsDead;
	
protected:
	
private:
	static FGenshinGameplayTags GameplayTags;
};