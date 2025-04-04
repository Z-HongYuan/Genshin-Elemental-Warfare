// Copyright © 2025 鸿源z 保留所有权利


#include "AbilitySystem/Attributes/GenshinAttributeSet.h"

#include "GameplayEffectExtension.h"
#include "Net/UnrealNetwork.h"

void UGenshinAttributeSet::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	/*`REPNOTIFY_Always` 告诉 `OnRep` 函数在本地值已经等于从服务器复制的值（由于预测）时触发。默认情况下，如果本地值与从服务器复制的值相同，则不会触发 `OnRep` 函数。*/
	DOREPLIFETIME_CONDITION_NOTIFY(UGenshinAttributeSet, Health, COND_None, REPNOTIFY_Always);	//确保属性终身复制
	DOREPLIFETIME_CONDITION_NOTIFY(UGenshinAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UGenshinAttributeSet, MoveSpeed, COND_None, REPNOTIFY_Always);
}

void UGenshinAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);
	if (Attribute == GetHealthAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.0f, GetMaxHealth());
	}
}

void UGenshinAttributeSet::PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		SetHealth(FMath::Clamp(GetHealth(), 0.0f, GetMaxHealth()));
	}
}
