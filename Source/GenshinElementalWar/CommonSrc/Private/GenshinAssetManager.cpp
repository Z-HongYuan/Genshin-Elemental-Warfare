// Copyright © 2025 鸿源z 保留所有权利


#include "GenshinElementalWar/CommonSrc/Public/GenshinAssetManager.h"

#include "GenshinElementalWar/CommonSrc/Public/GenshinGameplayTags.h"

UGenshinAssetManager& UGenshinAssetManager::Get()
{
	check(GEngine);
	
	return *Cast<UGenshinAssetManager>(GEngine->AssetManager);
}

void UGenshinAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();
	
	FGenshinGameplayTags::InitializeNativeGameplayTags();
}
