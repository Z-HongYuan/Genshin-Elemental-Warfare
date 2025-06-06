// Copyright © 2025 鸿源z 保留所有权利


#include "GenshinElementalWar/CommonSrc/Public/Character/Enemy/GenshinEnemy.h"


class UGenshinMovementComponent;

AGenshinEnemy::AGenshinEnemy(const class FObjectInitializer& ObjectInitializer):
Super(ObjectInitializer.SetDefaultSubobjectClass<UGenshinMovementComponent>(CharacterMovementComponentName))
{
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;	//启动复制

}

void AGenshinEnemy::BeginPlay()
{
	Super::BeginPlay();
	
	InitAbilitySystemComponent();
}

void AGenshinEnemy::InitAbilitySystemComponent()
{
	AbilitySystemComponent = CreateDefaultSubobject<UGenshinAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AttributeSet = CreateDefaultSubobject<UGenshinAttributeSet>(TEXT("AttributeSet"));
	AbilitySystemComponent->InitAbilityActorInfo(this, this);	//设置ASC信息
	AbilitySystemComponent->SetIsReplicated(true);	//设置ASC开启复制
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);	//设置复制模式 AI控制的Mode
	
	InitAttributeSet();
	InitStartAbilitiesAndEffects();
}
