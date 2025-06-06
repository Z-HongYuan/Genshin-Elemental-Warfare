// Copyright © 2025 鸿源z 保留所有权利


#include "GenshinElementalWar/CommonSrc/Public/Gameplay/Component/GenshinMovementComponent.h"
#include "GenshinElementalWar/CommonSrc/Public/Character/GenshinCharacterBase.h"


UGenshinMovementComponent::UGenshinMovementComponent()
{
}

float UGenshinMovementComponent::GetMaxSpeed() const
{
	const AGenshinCharacterBase* Owner = Cast<AGenshinCharacterBase>(GetOwner());
	
	if (!Owner or !Owner->GetAttributeSet())
	{
		return Super::GetMaxSpeed();
	}
	
	return Owner->GetAttributeSet()->GetMoveSpeed();
}
