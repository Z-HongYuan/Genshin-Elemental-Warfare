// Copyright © 2025 鸿源z 保留所有权利


#include "GenshinGameplayTags.h"
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
	UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Camera.NeedCamera"), TEXT("需要摄像机"));

	/*-------------输入Tag---------------*/
	UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Input.InputTag.LMB"), TEXT("鼠标左键"));
	UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Input.InputTag.RMB"), TEXT("鼠标右键"));
	/*-------------------------------*/
}
