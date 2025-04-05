// Copyright © 2025 鸿源z 保留所有权利


#include "AbilitySystem/Actor/GenshinWeaponActor.h"
#include "Character/GenshinCharacterBase.h"


AGenshinWeaponActor::AGenshinWeaponActor()
{
	PrimaryActorTick.bCanEverTick = true;
	
	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMesh"));
	WeaponMesh->SetupAttachment(RootComponent);
}

void AGenshinWeaponActor::AddAbilities()
{
	if (!IsValid(OwningCharacter) || !OwningCharacter->GetAbilitySystemComponent())
	{
		//log
		UE_LOG(LogTemp,Warning,TEXT("WeaponActor::AddAbilities() : OwningCharacter or OwningCharacter->GetAbilitySystemComponent() is nullptr"));
		return;	//防止空指针
	}
	if (UGenshinAbilitySystemComponent* ASC = Cast<UGenshinAbilitySystemComponent>(OwningCharacter->GetAbilitySystemComponent()))
	{
		for (TSubclassOf<UGenshinGameplayAbilityBase> Ability : Abilities)
		{
			FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(Ability,0, -1,this);
			AbilitySpecHandles.Add(ASC->GiveAbilityWithTag(AbilitySpec));
		}
	}
}

void AGenshinWeaponActor::RemoveAbilities()
{
	if (!IsValid(OwningCharacter) || !OwningCharacter->GetAbilitySystemComponent())
	{
		//log
		UE_LOG(LogTemp,Warning,TEXT("AGenshinWeaponActor::RemoveAbilities() : OwningCharacter or OwningCharacter->GetAbilitySystemComponent() is nullptr"));
		return;	//防止空指针
	}
	if (UGenshinAbilitySystemComponent* ASC = Cast<UGenshinAbilitySystemComponent>(OwningCharacter->GetAbilitySystemComponent()))
	{
		for (FGameplayAbilitySpecHandle& Handle : AbilitySpecHandles)
		{
			ASC->ClearAbility(Handle);	//根据保存的Handle来移除技能
		}
	}
}

void AGenshinWeaponActor::SetOwningCharacter(AGenshinCharacterBase* InOwningCharacter)
{
	OwningCharacter=InOwningCharacter;
	if(OwningCharacter)
	{
		AbilitySystem = OwningCharacter->GetAbilitySystemComponent();	//设置武器的ASC为角色的ASC
		SetOwner(OwningCharacter);	//设置武器的拥有者
		AttachToComponent(OwningCharacter->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);	//附加Actor到Character上
	}
	else
	{
		AbilitySystem = nullptr;
		SetOwner(nullptr);
		DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		
		//log
		UE_LOG(LogTemp,Warning,TEXT("AGenshinWeaponActor::SetOwningCharacter() : InOwningCharacter is nullptr"));
	}
}

void AGenshinWeaponActor::IsShowWeapon(const bool bShow) const
{
	WeaponMesh->CastShadow=bShow;
	WeaponMesh->bCastHiddenShadow = true;
	WeaponMesh->SetVisibility(!bShow,false);
	WeaponMesh->SetVisibility(bShow,false);
}

void AGenshinWeaponActor::ResetWeapon()
{
	ReloadAmmo(true);	//重新装填弹药
	ReloadAmmo(false);
	CurrentFireMode = DefaultFireMode;	//设置当前开火模式为默认开火模式
	
}

void AGenshinWeaponActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void AGenshinWeaponActor::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void AGenshinWeaponActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

