// Copyright © 2025 鸿源z 保留所有权利

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GenshinElementalWar/CommonSrc/Public/AbilitySystem/Attributes/GenshinAttributeSet.h"
#include "GenshinElementalWar/CommonSrc/Public/AbilitySystem/Component/GenshinAbilitySystemComponent.h"
#include "GameFramework/Actor.h"
#include "GenshinActorBase.generated.h"

/**
 * 带有ASC组件的Actor
 * 在Begin时创建ASC和Attribute
 * 建议需要ASC的Actor继承此基类
 */
UCLASS()
class GENSHINELEMENTALWAR_API AGenshinActorBase : public AActor, public IAbilitySystemInterface
{
	GENERATED_BODY()
	
public:	
	AGenshinActorBase();

	virtual UGenshinAbilitySystemComponent* GetAbilitySystemComponent() const override{return AbilitySystemComponent;}
	UGenshinAttributeSet* GetAttributeSet() const{return AttributeSet;}
protected:
	virtual void BeginPlay() override;

	UPROPERTY()
	TObjectPtr<UGenshinAbilitySystemComponent> AbilitySystemComponent;
	UPROPERTY()
	TObjectPtr<UGenshinAttributeSet> AttributeSet;

public:	
	virtual void Tick(float DeltaTime) override;

};
