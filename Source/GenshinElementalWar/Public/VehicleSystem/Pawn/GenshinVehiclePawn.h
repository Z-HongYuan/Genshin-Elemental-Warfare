// Copyright © 2025 鸿源z 保留所有权利

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "WheeledVehiclePawn.h"
#include "AbilitySystem/Attributes/GenshinAttributeSet.h"
#include "AbilitySystem/Component/GenshinAbilitySystemComponent.h"
#include "GenshinVehiclePawn.generated.h"

/**
 * 添加ASC组件
 * ??类似与Character为PlayerState添加GA还是自己拥有GA
 */
UCLASS()
class GENSHINELEMENTALWAR_API AGenshinVehiclePawn : public AWheeledVehiclePawn, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	AGenshinVehiclePawn();
	
	virtual UGenshinAbilitySystemComponent* GetAbilitySystemComponent() const override{return AbilitySystemComponent;}
	UGenshinAttributeSet* GetAttributeSet() const{return AttributeSet;}
	
	
protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AbilitySystem")
	TObjectPtr<UGenshinAbilitySystemComponent> AbilitySystemComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AbilitySystem")
	TObjectPtr<UGenshinAttributeSet> AttributeSet;
};
