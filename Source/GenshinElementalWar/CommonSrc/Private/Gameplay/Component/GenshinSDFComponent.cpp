// Copyright © 2025 鸿源z 保留所有权利


#include "GenshinElementalWar/CommonSrc/Public/Gameplay/Component/GenshinSDFComponent.h"

#include "ComponentUtils.h"

UGenshinSDFComponent::UGenshinSDFComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	SetIsReplicated(false);
	
	bHiddenInGame = true;
	FaceForwardValueName = "SDF_F";
	FaceRightValueName = "SDF_R";
	FaceForwardName = "SDF_F";
	FaceRightName = "SDF_R";
	HeadName = "Head";
}


//刷新面部材质实例,在更换角色的时候非常有用
void UGenshinSDFComponent::RefreshFaceMaterialInstance()
{
	if (FaceMaterialInstance != nullptr)
	{
		//TODO 调研是否需要ConditionalBeginDestroy,重置指针还是删除指针指向的材质
		FaceMaterialInstance->ConditionalBeginDestroy();
		//log
		UE_LOG(LogTemp,Warning,TEXT("UGenshinSDFComponent::RefreshFaceMaterialInstance() FaceMaterialInstance is BeginDestroy"));
	}
	
	ParentMeshComponent = Cast<USkeletalMeshComponent>(ComponentUtils::GetAttachedParent(this));
	
	if(ParentMeshComponent.Get())
	{
		//TODO 父类没有材质可供创建动态的时候,会崩溃
		FaceMaterialInstance = ParentMeshComponent.Get()->CreateDynamicMaterialInstance(FaceID, ParentMeshComponent.Get()->GetMaterial(FaceID),"FaceMI");
		//log
		UE_LOG(LogTemp,Log,TEXT("UGenshinSDFComponent::RefreshFaceMaterialInstance() FaceMaterialInstance is Created"));
	}
}


void UGenshinSDFComponent::BeginPlay()
{
	Super::BeginPlay();

	RefreshFaceMaterialInstance();
}

void UGenshinSDFComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	
	if (FaceMaterialInstance != nullptr)
	{
		FaceMaterialInstance->ConditionalBeginDestroy();
		UE_LOG(LogTemp,Log,TEXT("UGenshinSDFComponent::EndPlay() FaceMaterialInstance is BeginDestroy"));
	}
	
	ParentMeshComponent = nullptr;
	
	Super::EndPlay(EndPlayReason);
}


void UGenshinSDFComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	const FVector Forward = ParentMeshComponent->GetSocketLocation(FaceForwardName);
	const FVector Right = ParentMeshComponent->GetSocketLocation(FaceRightName);
	const FVector Head = ParentMeshComponent->GetSocketLocation(HeadName);

	if (FaceMaterialInstance and ParentMeshComponent.IsValid())
	{
		FaceMaterialInstance->SetVectorParameterValue(FaceForwardValueName,(Forward-Head).GetSafeNormal());
		FaceMaterialInstance->SetVectorParameterValue(FaceRightValueName,(Right-Head).GetSafeNormal());
	}
}

