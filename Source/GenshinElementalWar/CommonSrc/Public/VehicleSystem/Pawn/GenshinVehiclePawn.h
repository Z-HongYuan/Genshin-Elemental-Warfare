// Copyright © 2025 鸿源z 保留所有权利

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "WheeledVehiclePawn.h"
#include "GenshinElementalWar/CommonSrc/Public/AbilitySystem/Attributes/GenshinAttributeSet.h"
#include "GenshinElementalWar/CommonSrc/Public/AbilitySystem/Component/GenshinAbilitySystemComponent.h"
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

	//TODO 修改Ptr类型,使用WeakPtr,因为并不是跟Character的ASC强相关
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AbilitySystem")
	TObjectPtr<UGenshinAbilitySystemComponent> AbilitySystemComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AbilitySystem")
	TObjectPtr<UGenshinAttributeSet> AttributeSet;
};
