// Copyright © 2025 鸿源z 保留所有权利


#include "GenshinElementalWar/CommonSrc/Public/GenshinGameplayTags.h"
#include "GameplayTagsManager.h"

FGenshinGameplayTags FGenshinGameplayTags::GameplayTags;

void FGenshinGameplayTags::InitializeNativeGameplayTags()
{
	//保存一个变量,可以在Cpp中引用的添加
	GameplayTags.Tag_GameplayAbility_ActivateFail_IsDead = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("GameplayAbility.ActivateFail.IsDead"),
		TEXT("死亡")
		);

	//Cpp引用不了的添加
	// UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Camera.NeedCamera"), TEXT("需要摄像机"));

	/*-------------GA资产Tag---------------*/
	UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Ability.Character.Sprint"), TEXT("能力资产标签 冲刺"));
	/*-------------------------------*/

	/*-------------输入Tag---------------*/
	UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Input.InputTag.LMB"), TEXT("鼠标左键"));
	UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Input.InputTag.RMB"), TEXT("鼠标右键"));
	UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Input.AbilityInput.Sprint"), TEXT("能力标签 冲刺"));
	/*-------------------------------*/

	/*-----------------数据Tag--------------------*/
	UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Data.Ability.ChangeMoveSpeed"), TEXT("数据标签 用于改变移动速度"));
	/*-------------------------------*/


	/*-------------GE资产Tag---------------*/
	UGameplayTagsManager::Get().AddNativeGameplayTag(FName("GameplayEffect.Cost.Sprint"), TEXT("GE资产标签 冲刺"));
	/*-------------------------------*/

	/*-------------BlockTag---------------*/
	UGameplayTagsManager::Get().AddNativeGameplayTag(FName("BlockTag.StaminaRegenRate"), TEXT("BlockTag 阻挡Stamina恢复"));
	UGameplayTagsManager::Get().AddNativeGameplayTag(FName("BlockTag.ShieldRegenRate"), TEXT("BlockTag 阻挡Shield恢复"));
	/*-------------------------------*/
}
