// Copyright © 2025 鸿源z 保留所有权利


#include "GenshinElementalWar/CommonSrc/Public/Gameplay/GameMode/GenshinGameModeBase.h"

AGenshinGameModeBase::AGenshinGameModeBase()
{
	PrimaryActorTick.bCanEverTick = true;
	
	bUseSeamlessTravel = true;
}
