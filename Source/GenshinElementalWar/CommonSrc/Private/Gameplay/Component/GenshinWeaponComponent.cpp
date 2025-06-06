// Copyright © 2025 鸿源z 保留所有权利


#include "GenshinElementalWar/CommonSrc/Public/Gameplay/Component/GenshinWeaponComponent.h"


UGenshinWeaponComponent::UGenshinWeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	
}


void UGenshinWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	
	
}


void UGenshinWeaponComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
}

void UGenshinWeaponComponent::SpawnWeaponActors()
{
	for (TSubclassOf<AGenshinWeaponActor>& WeaponActor : WeaponActorClasses)
	{
		WeaponActorArray.Add(GetWorld()->SpawnActor<AGenshinWeaponActor>(WeaponActor));
	}
}

AGenshinWeaponActor* UGenshinWeaponComponent::GetWeaponActorByTag(FGameplayTag Tag)
{
	for (TObjectPtr<AGenshinWeaponActor>& Weapon : WeaponActorArray)
	{
		if (Weapon->WeaponTag == Tag)
		{
			return Weapon;
		}
	}
	return nullptr;
}

