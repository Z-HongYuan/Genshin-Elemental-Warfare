// Copyright © 2025 鸿源z 保留所有权利

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GenshinElementalWar/CommonSrc/Public/AbilitySystem/Attributes/GenshinAttributeSet.h"
#include "GenshinElementalWar/CommonSrc/Public/AbilitySystem/Component/GenshinAbilitySystemComponent.h"
#include "GameFramework/Character.h"
#include "GenshinElementalWar/CommonSrc/Public/Gameplay/Component/GenshinWeaponComponent.h"
#include "GenshinElementalWar/CommonSrc/Public/Gameplay/Component/GenshinMovementComponent.h"
#include "GenshinCharacterBase.generated.h"

/**
 * GenshinCharacter的基类\brief 
 * \b 需要自己创建ASC和Attribute \n
 * 实现了CoverMesh覆盖原Mesh\n
 * 实现了IAbilitySystemInterface的GetASC函数\n
 * 实现了GetAttributeSet函数\n
 * 重载了MovementComponent组件\n
 * 创建了InitAbilitySystemComponent虚函数\n
 * 实现了应用初始的Ability和Effect(包括通过GE应用的Attribute)\n
 * 实现了WeaponComponent组件\n
 */
UCLASS(Abstract, Category="Character")
class GENSHINELEMENTALWAR_API AGenshinCharacterBase : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	AGenshinCharacterBase(const class FObjectInitializer& ObjectInitializer);	//重载自定义CMC组件

	//获取AbilitySystemComponent
	virtual UGenshinAbilitySystemComponent* GetAbilitySystemComponent()const override{return AbilitySystemComponent;}
	//获取AttributeSet
	UGenshinAttributeSet* GetAttributeSet()const { return AttributeSet;}

	//获取CoverMesh
	UFUNCTION(BlueprintPure, Category="GenshinFun")
	USkeletalMeshComponent* GetCoverMesh()const {return CoverMesh;} 

protected:

	/*--------------------拥有的组件-------------------------------------------*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"), Category="Weapon")
	TObjectPtr<UGenshinWeaponComponent> WeaponComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"), Category="Character")	//Copy的Character的Mesh
	TObjectPtr<USkeletalMeshComponent> CoverMesh;

	// UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"), Category="Components")
	// TObjectPtr<UGenshinSDFComponent> SDFComponent;		//只有在Player里面有
	/*----------------------------------------------------------------------------------*/
	
	/*----------------------AbilitySystem相关--------------------------------*/
	UPROPERTY()
	TObjectPtr<UGenshinAbilitySystemComponent> AbilitySystemComponent;
	UPROPERTY()
	TObjectPtr<UGenshinAttributeSet> AttributeSet;

	//初始属性集
	UPROPERTY(EditDefaultsOnly, Category = "AbilitySystem")
	TSubclassOf<UGameplayEffect> StartupAttribute;

	//初始GE效果
	UPROPERTY(EditDefaultsOnly, Category = "AbilitySystem")
	TArray<TSubclassOf<UGameplayEffect>> StartupEffects;

	//初始能力
	UPROPERTY(EditDefaultsOnly, Category = "AbilitySystem")
	TArray<TSubclassOf<UGameplayAbility>> StartupAbilities;

	//初始能力并且执行一次
	UPROPERTY(EditDefaultsOnly, Category = "AbilitySystem")
	TArray<TSubclassOf<UGameplayAbility>> StartupDoOnceAbilities;

	//初始化AbilitySystemComponent,不做任何事,将在子类中实现
	virtual void InitAbilitySystemComponent();
	void InitAttributeSet() const;	//必须调用,全部Give的Level=-1,使用GE初始化AttributeSet
	void InitStartAbilitiesAndEffects();	//必须调用,全部Give的Level=-1
	/*--------------------------------------------------------------------------*/
	
};
