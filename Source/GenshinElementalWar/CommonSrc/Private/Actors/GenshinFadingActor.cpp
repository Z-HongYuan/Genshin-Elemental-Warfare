// Copyright © 2025 鸿源z 保留所有权利


#include "GenshinElementalWar/CommonSrc/Public/Actors/GenshinFadingActor.h"
#include "GenshinElementalWar/CommonSrc/Public/Character/GenshinCharacterBase.h"

AGenshinFadingActor::AGenshinFadingActor()
{
	PrimaryActorTick.bCanEverTick = true;
	
	PoseableMesh = CreateDefaultSubobject<UPoseableMeshComponent>(TEXT("PoseableMesh"));
	
	FadeMaterialStartValue = -1.0f;
	FadeMaterialEndValue = 1.0f;
	FadeStartDelayTime = FadeEndDelayTime = 1.0f;
	bIsBeginFade = false;
	FadeMaterialName = "BodyAlphaControll";
}

void AGenshinFadingActor::BeginPlay()
{
	Super::BeginPlay();

	if (const AGenshinCharacterBase* CharacterBase = Cast<AGenshinCharacterBase>(GetOwner()))
	{
		PoseableMesh->SetSkinnedAssetAndUpdate(CharacterBase->GetCoverMesh()->GetSkeletalMeshAsset());
		PoseableMesh->CopyPoseFromSkeletalComponent(CharacterBase->GetCoverMesh());
		
		//淡化前的延迟
		GetWorldTimerManager().SetTimer(FadeStartDelayTimerHandle, this, &AGenshinFadingActor::FadeStartDelay, 1, false, FadeStartDelayTime);
	}
	else
	{
		//log
		UE_LOG(LogTemp, Warning, TEXT("AGenshinFadingActor::BeginPlay() Owner is not GenshinCharacter"));
		this->Destroy();
	}
}

void AGenshinFadingActor::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (FadeStartDelayTimerHandle.IsValid())
	{
		GetWorldTimerManager().ClearTimer(FadeStartDelayTimerHandle);
		FadeStartDelayTimerHandle.Invalidate();
	}
	if (FadeEndDelayTimerHandle.IsValid())
	{
		GetWorldTimerManager().ClearTimer(FadeEndDelayTimerHandle);
		FadeEndDelayTimerHandle.Invalidate();
	}

	Super::EndPlay(EndPlayReason);
}

void AGenshinFadingActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIsBeginFade)
	{
		FadeMaterialStartValue = FMath::FInterpTo(FadeMaterialStartValue, FadeMaterialEndValue, DeltaTime, FadeSpeed);
		PoseableMesh->SetScalarParameterValueOnMaterials(FadeMaterialName, FadeMaterialStartValue);
	}
	
	//淡化结束的定时器回调,无论如何,只会执行一次
	if (FMath::IsNearlyEqual(FadeMaterialStartValue, FadeMaterialEndValue,0.001f) and bIsBeginFade)
	{
		bIsBeginFade = false;
		GetWorldTimerManager().SetTimer(FadeEndDelayTimerHandle, this, &AGenshinFadingActor::FadeEndDelay, 1, false, FadeEndDelayTime);
	}
}

