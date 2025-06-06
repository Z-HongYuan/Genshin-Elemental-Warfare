// Copyright © 2025 鸿源z 保留所有权利

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GenshinElementalWar/CommonSrc/Public/AbilitySystem/Attributes/GenshinAttributeSet.h"
#include "GenshinElementalWar/CommonSrc/Public/AbilitySystem/Component/GenshinAbilitySystemComponent.h"
#include "GameFramework/PlayerState.h"
#include "GenshinPlayerState.generated.h"

/**
 * 为多人游戏开发
 * 玩家的ASC和Attribute组件实际在此处
 */
UCLASS()
class GENSHINELEMENTALWAR_API AGenshinPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	AGenshinPlayerState();

	//返回ASC
	virtual UGenshinAbilitySystemComponent* GetAbilitySystemComponent() const override{return AbilitySystemComponent;}
	//返回AttributeSet
	UGenshinAttributeSet* GetAttributeSet() const{return AttributeSet;}
	
protected:
	UPROPERTY()
	TObjectPtr<UGenshinAbilitySystemComponent> AbilitySystemComponent;
	UPROPERTY()
	TObjectPtr<UGenshinAttributeSet> AttributeSet;
};
