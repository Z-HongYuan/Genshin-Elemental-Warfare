// Copyright © 2025 鸿源z 保留所有权利


#include "GenshinElementalWar/CommonSrc/Public/Gameplay/PlayerState/GenshinPlayerState.h"

AGenshinPlayerState::AGenshinPlayerState()
{
	bReplicates = true;	//设置复制
	SetNetUpdateFrequency(200.f);	//设置网络同步速度
	SetMinNetUpdateFrequency(100.f);	//设置网络同步速度
	
	AbilitySystemComponent = CreateDefaultSubobject<UGenshinAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);	//启动复制
	AttributeSet = CreateDefaultSubobject<UGenshinAttributeSet>(TEXT("AttributeSet"));
}
