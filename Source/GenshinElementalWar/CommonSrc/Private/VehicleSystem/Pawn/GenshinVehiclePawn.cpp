// Copyright © 2025 鸿源z 保留所有权利


#include "GenshinElementalWar/CommonSrc/Public/VehicleSystem/Pawn/GenshinVehiclePawn.h"

AGenshinVehiclePawn::AGenshinVehiclePawn()
{
	AbilitySystemComponent = CreateDefaultSubobject<UGenshinAbilitySystemComponent>(TEXT("AbilitySystem"));
	AttributeSet = CreateDefaultSubobject<UGenshinAttributeSet>(TEXT("AttributeSet"));
}

void AGenshinVehiclePawn::BeginPlay()
{
	Super::BeginPlay();
}
