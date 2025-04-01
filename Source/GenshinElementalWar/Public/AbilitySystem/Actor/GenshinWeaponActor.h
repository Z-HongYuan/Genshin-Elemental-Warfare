// Copyright © 2025 鸿源z 保留所有权利

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameplayTagContainer.h"
#include "AbilitySystem/Component/GenshinAbilitySystemComponent.h"
#include "GenshinWeaponActor.generated.h"


/*
 * WeaponActor
 * 拥有Tag用于识别
 */
class AGenshinCharacterBase;
UCLASS()
class GENSHINELEMENTALWAR_API AGenshinWeaponActor : public AActor, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	AGenshinWeaponActor();

	//用于标识武器
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Weapon")
	FGameplayTag WeaponTag;

	//默认的射击模式,用于重置
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly, Category = "Weapon")
	FGameplayTag DefaultFireMode;

	/*
	 *武器的Icon 可能不需要,这关于UI 系统
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "AbilitySystem|UI")
	UPaperSprite* WeaponIcon;
	*/

	//用于在GA中使用,获取Mesh相关的位置
	UFUNCTION(BlueprintPure, Category = "Weapon")
	virtual USkeletalMeshComponent* GetWeaponMesh() const{return WeaponMesh;}
	
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override{return AbilitySystem;}
	
	//设置拥有者
	void SetOwningCharacter(AGenshinCharacterBase* InOwningCharacter);

	//显示或者隐藏Weapon
	void IsShowWeapon(bool bShow) const;

	//刷新Weapon的函数
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void ResetWeapon();

	//用于获取当前剩余的子弹数量
	UFUNCTION(BlueprintPure, Category = "Weapon")
	int32 GetWeaponAmmo(bool bIsPrimary) const {
		if (bIsPrimary)
		{
			return WeaponPrimaryAmmo;
		}
		return WeaponSecondaryAmmo;
	}

	//重新装填子弹
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	virtual void ReloadAmmo(bool bIsPrimary) { bIsPrimary? WeaponPrimaryAmmo = WeaponPrimaryMaxAmmo : WeaponSecondaryAmmo = WeaponSecondaryMaxAmmo;}

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	
	//主要的WeaponMesh
	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly, Category = "Weapon")
	TObjectPtr<USkeletalMeshComponent> WeaponMesh;
	
	//自己并不附带ASC组件,需要使用Owner的ASC填充Ptr
	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly, Category = "Weapon")
	TObjectPtr<UGenshinAbilitySystemComponent> AbilitySystem;

	//拥有者
	UPROPERTY(BlueprintReadOnly, Category = "Weapon")
	TObjectPtr<AGenshinCharacterBase> OwningCharacter;
	
	//当前使用的射击模式
	UPROPERTY(BlueprintReadWrite, VisibleInstanceOnly, Category = "Weapon")
	FGameplayTag CurrentFireMode;
	
	UPROPERTY()
	int32 WeaponPrimaryAmmo;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
	int32 WeaponPrimaryMaxAmmo;
	
	UPROPERTY()
	int32 WeaponSecondaryAmmo;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
	int32 WeaponSecondaryMaxAmmo;
	
	//给予Owner的技能
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Weapon")
	TArray<TSubclassOf<UGenshinGameplayAbilityBase>> Abilities;

	//AbilitySpecHandle,用于保存技能添加后的Handle,以便移除
	UPROPERTY(BlueprintReadOnly, Category = "Weapon")
	TArray<FGameplayAbilitySpecHandle> AbilitySpecHandles;
	
	//将在Weapon装载或者切换的时候调用
	virtual void AddAbilities();

	//将在Weapon移除或者切换或者卸载的时候调用
	virtual void RemoveAbilities();
public:
	virtual void Tick(float DeltaTime) override;
};
