 // Copyright © 2025 鸿源z 保留所有权利

#pragma once

#include "CoreMinimal.h"
#include "GenshinElementalWar/CommonSrc/Public/AbilitySystem/Actor/GenshinWeaponActor.h"
#include "Components/ActorComponent.h"
#include "GenshinWeaponComponent.generated.h"

/*
 * 包含WeaponActor数组的组件
 * 提供对与WeaponActor的管理
 * WeaponActor作为最小单元为Actor提供更高层的管理功能
 */

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GENSHINELEMENTALWAR_API UGenshinWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UGenshinWeaponComponent();
	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	UFUNCTION(BlueprintCallable, Category = "Weapon")	//生成所有WeaponActor
	void SpawnWeaponActors();
	
	UFUNCTION(BlueprintPure, Category = "Weapon")	//获取当前WeaponActor
	AGenshinWeaponActor* GetCurrentWeapon() {return CurrentWeapon;}	
	
	UFUNCTION(BlueprintPure, Category = "Weapon")	//获取所有的WeaponActor数组
	TArray<AGenshinWeaponActor*> GetWeaponActorArray() {return WeaponActorArray;}
	
	UFUNCTION(BlueprintPure, Category = "Weapon")	//通过Tag获取WeaponActor
	AGenshinWeaponActor* GetWeaponActorByTag(FGameplayTag Tag);
protected:
	UPROPERTY(BlueprintReadOnly, Category = "Weapon")
	TArray<TObjectPtr<AGenshinWeaponActor>> WeaponActorArray;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	TArray<TSubclassOf<AGenshinWeaponActor>> WeaponActorClasses;

	UPROPERTY()
	TObjectPtr<AGenshinWeaponActor> CurrentWeapon;
	
	virtual void BeginPlay() override;
	
};
