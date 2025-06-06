// Copyright © 2025 鸿源z 保留所有权利


#include "GenshinElementalWar/CommonSrc/Public/AbilitySystem/Attributes/GenshinAttributeSet.h"

#include "GameplayEffectExtension.h"
#include "Net/UnrealNetwork.h"

void UGenshinAttributeSet::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	/*`REPNOTIFY_Always` 告诉 `OnRep` 函数在本地值已经等于从服务器复制的值（由于预测）时触发。默认情况下，如果本地值与从服务器复制的值相同，则不会触发 `OnRep` 函数。*/
	DOREPLIFETIME_CONDITION_NOTIFY(UGenshinAttributeSet, Health, COND_None, REPNOTIFY_Always);	//确保属性终身复制
	DOREPLIFETIME_CONDITION_NOTIFY(UGenshinAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UGenshinAttributeSet, Stamina, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UGenshinAttributeSet, MaxStamina, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UGenshinAttributeSet, StaminaRegenRate, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UGenshinAttributeSet, Shield, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UGenshinAttributeSet, MaxShield, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UGenshinAttributeSet, ShieldRegenRate, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UGenshinAttributeSet, MoveSpeed, COND_None, REPNOTIFY_Always);
}

void UGenshinAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UGenshinAttributeSet, Health, OldHealth);
}

void UGenshinAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UGenshinAttributeSet, MaxHealth, OldMaxHealth);
}

void UGenshinAttributeSet::OnRep_Stamina(const FGameplayAttributeData& OldStamina)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UGenshinAttributeSet, Stamina, OldStamina);
}

void UGenshinAttributeSet::OnRep_MaxStamina(const FGameplayAttributeData& OldMaxStamina)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UGenshinAttributeSet, MaxStamina, OldMaxStamina);
}

void UGenshinAttributeSet::OnRep_StaminaRegenRate(const FGameplayAttributeData& OldStaminaRegenRate)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UGenshinAttributeSet, StaminaRegenRate, OldStaminaRegenRate);
}

void UGenshinAttributeSet::OnRep_Shield(const FGameplayAttributeData& OldShield)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UGenshinAttributeSet, Shield, OldShield);
}

void UGenshinAttributeSet::OnRep_MaxShield(const FGameplayAttributeData& OldMaxShield)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UGenshinAttributeSet, MaxShield, OldMaxShield);
}

void UGenshinAttributeSet::OnRep_ShieldRegenRate(const FGameplayAttributeData& OldShieldRegenRate)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UGenshinAttributeSet, ShieldRegenRate, OldShieldRegenRate);
}

void UGenshinAttributeSet::OnRep_MoveSpeed(const FGameplayAttributeData& OldMoveSpeed)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UGenshinAttributeSet, MoveSpeed, OldMoveSpeed);
}

void UGenshinAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);
	
	if (Attribute == GetMoveSpeedAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.0f, 99999.0f);
	}
	if (Attribute == GetHealthAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.0f, GetMaxHealth());
	}
	if (Attribute == GetStaminaAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.0f, GetMaxStamina());
	}
}

void UGenshinAttributeSet::PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
	
	if (Data.EvaluatedData.Attribute == GetMoveSpeedAttribute())
	{
		SetMoveSpeed(FMath::Clamp(GetMoveSpeed(), 0.0f, 99999.0f));
	}
	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		SetHealth(FMath::Clamp(GetHealth(), 0.0f, GetMaxHealth()));
	}
	if (Data.EvaluatedData.Attribute == GetStaminaAttribute())
	{
		SetStamina(FMath::Clamp(GetStamina(), 0.0f, GetMaxStamina()));
	}
}
