// Copyright © 2025 鸿源z 保留所有权利

#pragma once

#include "CoreMinimal.h"
#include "GenshinElementalWar/CommonSrc/Public/Character/GenshinCharacterBase.h"
#include "GenshinEnemy.generated.h"

/**
 * 带有ASC组件,将在Begin时Init
 */
UCLASS()
class GENSHINELEMENTALWAR_API AGenshinEnemy : public AGenshinCharacterBase
{
	GENERATED_BODY()

public:
	AGenshinEnemy(const class FObjectInitializer& ObjectInitializer);

	virtual void BeginPlay() override;
protected:
	virtual void InitAbilitySystemComponent() override;
};
