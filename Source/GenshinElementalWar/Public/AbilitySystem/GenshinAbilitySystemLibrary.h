// Copyright © 2025 鸿源z 保留所有权利

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "GenshinAbilitySystemLibrary.generated.h"


/**
 * 
 */
UCLASS()
class GENSHINELEMENTALWAR_API UGenshinAbilitySystemLibrary : public UAbilitySystemBlueprintLibrary
{
	GENERATED_BODY()

	/*
	 *使用的组件搜索,也许会有性能损耗
	UFUNCTION(BlueprintPure, Category = Attribute, Meta=(DefaultToSelf = "Actor"))
	static UGenshinAttributeSet* GetAttributeSet(AActor* Actor, bool LookForComponent=true);
	没用
	*/
};
