// Copyright © 2025 鸿源z 保留所有权利


#include "AbilitySystem/Actor/GenshinActorBase.h"


AGenshinActorBase::AGenshinActorBase()
{
	PrimaryActorTick.bCanEverTick = true;

}


void AGenshinActorBase::BeginPlay()
{
	Super::BeginPlay();

	AbilitySystemComponent = CreateDefaultSubobject<UGenshinAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AttributeSet = CreateDefaultSubobject<UGenshinAttributeSet>(TEXT("AttributeSet"));
}


void AGenshinActorBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

