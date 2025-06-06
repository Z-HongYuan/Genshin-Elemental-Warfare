// Copyright © 2025 鸿源z 保留所有权利


#include "GenshinElementalWar/CommonSrc/Public/Animation/GenshinAnimInstance.h"
#include "AbilitySystemGlobals.h"

void UGenshinAnimInstance::SetGameplayTagPropertyMap(AActor* ListenInActor)
{
	if (UAbilitySystemComponent* ASC = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(ListenInActor))
	{
		check(ASC);
		GameplayTagPropertyMap.Initialize(this,ASC);
	}
}

