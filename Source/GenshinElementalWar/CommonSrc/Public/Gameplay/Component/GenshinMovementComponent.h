// Copyright © 2025 鸿源z 保留所有权利

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GenshinMovementComponent.generated.h"


/**
 * 与角色耦合的移动组件
 * 覆写了 GetMaxSpeed()，根据属性返回最大速度
 */
UCLASS()
class GENSHINELEMENTALWAR_API UGenshinMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()

public:
	UGenshinMovementComponent();
	
	virtual float GetMaxSpeed() const override;
	
};
