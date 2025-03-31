// Copyright © 2025 鸿源z 保留所有权利

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "GenshinAssetManager.generated.h"

/**
 * 资产管理器
 * 单例,全局唯一
 * 
 */
UCLASS()
class GENSHINELEMENTALWAR_API UGenshinAssetManager : public UAssetManager
{
	GENERATED_BODY()
	
public:
	static UGenshinAssetManager& Get();

protected:

	//注册资产,Tag资产
	virtual void StartInitialLoading() override;
};
