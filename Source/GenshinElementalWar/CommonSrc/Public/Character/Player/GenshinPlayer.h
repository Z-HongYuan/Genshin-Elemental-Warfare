// Copyright © 2025 鸿源z 保留所有权利

#pragma once

#include "CoreMinimal.h"
#include "GenshinElementalWar/CommonSrc/Public/Character/GenshinCharacterBase.h"
#include "GameFramework/GameplayCameraComponent.h"
#include "GenshinElementalWar/CommonSrc/Public/Gameplay/Component/GenshinSDFComponent.h"
#include "GenshinPlayer.generated.h"

/**
 * 带有ASC组件,将在PlayerState中Init,(Local ASC)->(PS ASC)
 */
UCLASS()
class GENSHINELEMENTALWAR_API AGenshinPlayer : public AGenshinCharacterBase
{
	GENERATED_BODY()

public:
	AGenshinPlayer(const class FObjectInitializer& ObjectInitializer);

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"), Category="Components")
	TObjectPtr<UGenshinSDFComponent> SDFComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"), Category="Components")
	TObjectPtr<UGameplayCameraComponent> GameplayCamera;
	
	virtual void BeginPlay() override;
	
	virtual void PossessedBy(AController* NewController) override;

	//仅限拥有的客户端
	UFUNCTION(BlueprintCallable,Client,Reliable)
	void SetupCamera_RunOnClient();
	void SetupCamera_RunOnClient_Implementation();
	
	virtual void OnRep_PlayerState() override;
	
	virtual void InitAbilitySystemComponent() override;	//初始化ASC入口
	
};
