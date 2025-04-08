// Copyright © 2025 鸿源z 保留所有权利


#include "Actors/GenshinProjectileActor.h"


AGenshinProjectileActor::AGenshinProjectileActor()
{
	PrimaryActorTick.bCanEverTick = true;

	//抛射物移动组件
	ProjectileMovementComponent=CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	ProjectileMovementComponent->InitialSpeed=3000.0f;
	ProjectileMovementComponent->ProjectileGravityScale=1.0f;
	
	//碰撞体
	CapsuleComponent=CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
	CapsuleComponent->SetupAttachment(RootComponent);
	CapsuleComponent->SetCollisionProfileName(TEXT("Projectile"));
	CapsuleComponent->CanCharacterStepUpOn=ECanBeCharacterBase::ECB_No;
	CapsuleComponent->SetAllUseCCD(true);

	//抛射物网格体
	ProjectileMesh=CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMesh"));
	ProjectileMesh->SetupAttachment(CapsuleComponent);
	ProjectileMesh->SetCollisionProfileName(TEXT("NoCollision"));
	ProjectileMesh->CanCharacterStepUpOn=ECanBeCharacterBase::ECB_No;
	ProjectileMesh->SetGenerateOverlapEvents(false);
}

void AGenshinProjectileActor::ApplyEffectToOverlap(AActor* ApplyActor, bool bIgnorePlayer)
{
}

void AGenshinProjectileActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void AGenshinProjectileActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

