// Copyright © 2025 鸿源z 保留所有权利

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectTypes.h"
#include "Animation/AnimInstance.h"
#include "GenshinAnimInstance.generated.h"

/**
 * 带有 GameplayTagMap 的 AnimInstance
 */
UCLASS()
class GENSHINELEMENTALWAR_API UGenshinAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
public:
	
	UFUNCTION(BlueprintCallable, Category = "GameplayTags")
	void SetGameplayTagPropertyMap(AActor* ListenInActor);
	
protected:
	UPROPERTY(EditDefaultsOnly, Category = "GameplayTags")
	FGameplayTagBlueprintPropertyMap GameplayTagPropertyMap;
};
