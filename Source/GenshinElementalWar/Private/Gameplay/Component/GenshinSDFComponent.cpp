// Copyright © 2025 鸿源z 保留所有权利


#include "Gameplay/Component/GenshinSDFComponent.h"

#include "ComponentUtils.h"

UGenshinSDFComponent::UGenshinSDFComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	bHiddenInGame = true;
}


//刷新面部材质实例,在更换角色的时候非常有用
void UGenshinSDFComponent::RefreshFaceMaterialInstance()
{
	if (FaceMaterialInstance != nullptr)
	{
		FaceMaterialInstance->ConditionalBeginDestroy();
	}
	
	ParentMeshComponent = Cast<USkeletalMeshComponent>(ComponentUtils::GetAttachedParent(this));
	
	if(ParentMeshComponent)
	{
		//TODO 父类没有材质可供创建动态的时候,会崩溃
		FaceMaterialInstance = ParentMeshComponent->CreateDynamicMaterialInstance(FaceID, ParentMeshComponent->GetMaterial(FaceID),"FaceMI");
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

	FaceMaterialInstance->SetVectorParameterValue(FaceForwardValueName,(Forward-Head).GetSafeNormal());
	FaceMaterialInstance->SetVectorParameterValue(FaceRightValueName,(Right-Head).GetSafeNormal());
}

