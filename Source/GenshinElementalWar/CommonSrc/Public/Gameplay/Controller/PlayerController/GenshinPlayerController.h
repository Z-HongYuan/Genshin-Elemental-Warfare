// Copyright © 2025 鸿源z 保留所有权利

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "GameplayTagContainer.h"
#include "GenshinElementalWar/CommonSrc/Public/AbilitySystem/Component/GenshinAbilitySystemComponent.h"
#include "GenshinPlayerController.generated.h"

class UGenshinInputDataAsset;
class UInputMappingContext;
/**
 * 设置了玩家摄像机管理器
 * 设置了CheatManager
 * 添加了对Ability的输入支持
 */
UCLASS()
class GENSHINELEMENTALWAR_API AGenshinPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	AGenshinPlayerController();

	//视角缩放
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Input")
	float LeftRightRate = 0.75;
	
	//视角缩放
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Input")
	float UpDownRate = 0.75;

	virtual void BeginPlay() override;

	virtual void SetupInputComponent() override;
protected:
	//优先级为 0 的输入上下文
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputMappingContext> DefaultContext;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputAction> MoveAction;
	
	UPROPERTY(EditAnywhere,Category="Input")
	TObjectPtr<UInputAction> LookAction;

	//Ability与Tag对应的数据资产
	UPROPERTY(EditDefaultsOnly,Category="Input")
	TObjectPtr<UGenshinInputDataAsset> InputDataAsset;

	//默认需要的Move/Look回调函数
	void HandleMove(const FInputActionValue& Value);
	void HandleLook(const FInputActionValue& Value);

	//用于在ASC内触发输入的函数
	void AbilityInputTagPressed(FGameplayTag InputTag);
	void AbilityInputTagReleased(FGameplayTag InputTag);
	void AbilityInputTagHeld(FGameplayTag InputTag);
	
	//TWeakObjectPtr的ASC,用于Get单例
	TWeakObjectPtr<UGenshinAbilitySystemComponent> GenshinAbilitySystemComponent;
	UGenshinAbilitySystemComponent* GetASC();
};
