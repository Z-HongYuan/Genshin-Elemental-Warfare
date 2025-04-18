// Copyright © 2025 鸿源z 保留所有权利

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "GenshinAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

/**
 * 属性集,这是一个Base属性集.
 * 也许后期会有子类继承这个属性集.
 */
UCLASS()
class GENSHINELEMENTALWAR_API UGenshinAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	//复制函数
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;


	//Health
	UPROPERTY(BlueprintReadOnly, Category = "BaseAttributes", ReplicatedUsing = OnRep_Health)
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UGenshinAttributeSet, Health)
	UFUNCTION()
	virtual void OnRep_Health(const FGameplayAttributeData& OldHealth);
	
	//最大生命值
	UPROPERTY(BlueprintReadOnly, Category = "BaseAttributes", ReplicatedUsing = OnRep_MaxHealth)
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UGenshinAttributeSet, MaxHealth)
	UFUNCTION()
	virtual void OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth);

	//体力值
	UPROPERTY(BlueprintReadOnly, Category = "BaseAttributes", ReplicatedUsing = OnRep_Stamina)
	FGameplayAttributeData Stamina;
	ATTRIBUTE_ACCESSORS(UGenshinAttributeSet, Stamina)
	UFUNCTION()
	virtual void OnRep_Stamina(const FGameplayAttributeData& OldStamina);

	//最大体力值
	UPROPERTY(BlueprintReadOnly, Category = "BaseAttributes", ReplicatedUsing = OnRep_MaxStamina)
	FGameplayAttributeData MaxStamina;
	ATTRIBUTE_ACCESSORS(UGenshinAttributeSet, MaxStamina)
	UFUNCTION()
	virtual void OnRep_MaxStamina(const FGameplayAttributeData& OldMaxStamina);

	//体力值恢复速度
	UPROPERTY(BlueprintReadOnly, Category = "BaseAttributes", ReplicatedUsing = OnRep_StaminaRegenRate)
	FGameplayAttributeData StaminaRegenRate;
	ATTRIBUTE_ACCESSORS(UGenshinAttributeSet, StaminaRegenRate)
	UFUNCTION()
	virtual void OnRep_StaminaRegenRate(const FGameplayAttributeData& OldStaminaRegenRate);

	//护盾值
	UPROPERTY(BlueprintReadOnly, Category = "BaseAttributes", ReplicatedUsing = OnRep_Shield)
	FGameplayAttributeData Shield;
	ATTRIBUTE_ACCESSORS(UGenshinAttributeSet, Shield)
	UFUNCTION()
	virtual void OnRep_Shield(const FGameplayAttributeData& OldShield);

	//最大护盾值
	UPROPERTY(BlueprintReadOnly, Category = "BaseAttributes", ReplicatedUsing = OnRep_MaxShield)
	FGameplayAttributeData MaxShield;
	ATTRIBUTE_ACCESSORS(UGenshinAttributeSet, MaxShield)
	UFUNCTION()
	virtual void OnRep_MaxShield(const FGameplayAttributeData& OldMaxShield);

	//护盾值恢复速度
	UPROPERTY(BlueprintReadOnly, Category = "BaseAttributes", ReplicatedUsing = OnRep_ShieldRegenRate)
	FGameplayAttributeData ShieldRegenRate;
	ATTRIBUTE_ACCESSORS(UGenshinAttributeSet, ShieldRegenRate)
	UFUNCTION()
	virtual void OnRep_ShieldRegenRate(const FGameplayAttributeData& OldShieldRegenRate);
	
	//移动速度
	UPROPERTY(BlueprintReadOnly, Category = "Movement", ReplicatedUsing = OnRep_MoveSpeed)
	FGameplayAttributeData MoveSpeed;
	ATTRIBUTE_ACCESSORS(UGenshinAttributeSet, MoveSpeed)
	UFUNCTION()
	virtual void OnRep_MoveSpeed(const FGameplayAttributeData& OldMoveSpeed);

	
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	
	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;
};
