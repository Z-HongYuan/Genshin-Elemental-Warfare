// Copyright © 2025 鸿源z 保留所有权利


#include "GenshinElementalWar/CommonSrc/Public/Character/GenshinCharacterBase.h"
#include "GenshinElementalWar/CommonSrc/Public/AbilitySystem/Abilities/GenshinGameplayAbilityBase.h"


AGenshinCharacterBase::AGenshinCharacterBase(const class FObjectInitializer& ObjectInitializer) :
Super(ObjectInitializer.SetDefaultSubobjectClass<UGenshinMovementComponent>(CharacterMovementComponentName))
{
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;	//启动复制
	
	GetMesh()->bPropagateCurvesToFollowers = true;	// 曲线同步到子Mesh
	GetMesh()->SetCollisionProfileName("NoCollision");	//无碰撞
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);	//无碰撞
	GetMesh()->CastShadow = false;	//不投射阴影
	GetMesh()->SetVisibleFlag(false);	//不可见
	GetMesh()->VisibilityBasedAnimTickOption=EVisibilityBasedAnimTickOption::AlwaysTickPoseAndRefreshBones;	//总是刷新动画和骨骼
	
	CoverMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CoverMesh"));	//创建CoverMesh
	CoverMesh->SetupAttachment(GetMesh());	//附加到原本的Mesh上
	CoverMesh->SetRenderCustomDepth(true);	//启用自定义深度渲染

	WeaponComponent = CreateDefaultSubobject<UGenshinWeaponComponent>(TEXT("WeaponComponent"));	//创建武器组件
}

//不做任何事,将在子类中实现
void AGenshinCharacterBase::InitAbilitySystemComponent()
{
	//不做任何事,将在子类中实现
}

void AGenshinCharacterBase::InitAttributeSet() const
{
	if (GetAbilitySystemComponent() and StartupAttribute)
	{
		GetAbilitySystemComponent()->ApplyGameplayEffectSpecToTarget(*GetAbilitySystemComponent()->MakeOutgoingSpec(
			StartupAttribute,
			-1,
			GetAbilitySystemComponent()->MakeEffectContext()
			).Data.Get(),GetAbilitySystemComponent());
	}
}

void AGenshinCharacterBase::InitStartAbilitiesAndEffects()
{
	for (TSubclassOf<UGameplayEffect>& Effect : StartupEffects)
	{
		if (!Effect) continue;
		FGameplayEffectContextHandle ContextHandle=GetAbilitySystemComponent()->MakeEffectContext();
		FGameplayEffectSpecHandle SpecHandle=GetAbilitySystemComponent()->MakeOutgoingSpec(Effect,-1,ContextHandle);
		GetAbilitySystemComponent()->ApplyGameplayEffectSpecToTarget(*SpecHandle.Data.Get(),GetAbilitySystemComponent());
	}

	//服务端Give
	if (HasAuthority())
	{
		for (TSubclassOf<UGameplayAbility>& Ability : StartupAbilities)
		{
			if (!Ability) continue;
			FGameplayAbilitySpec AbilitySpec=FGameplayAbilitySpec(Ability,-1,-1,this);
			GetAbilitySystemComponent()->GiveAbilityWithTag(AbilitySpec);
		}
	}

	//服务端Give
	if (HasAuthority())
	{
		for (TSubclassOf<UGameplayAbility>& Ability : StartupDoOnceAbilities)
		{
			if (!Ability) continue;
			FGameplayAbilitySpec AbilitySpec(Ability,-1,-1,this);
			GetAbilitySystemComponent()->GiveAbilityAndActivateOnce(AbilitySpec);
		}
	}
}

