// Copyright © 2025 鸿源z 保留所有权利


#include "Gameplay/Component/GenshinSDFComponent.h"

#include "ComponentUtils.h"

UGenshinSDFComponent::UGenshinSDFComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
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
		FaceMaterialInstance->ConditionalBeginDestroy();
		//log
		UE_LOG(LogTemp,Warning,TEXT("UGenshinSDFComponent::RefreshFaceMaterialInstance() FaceMaterialInstance is BeginDestroy"));
	}
	
	ParentMeshComponent = Cast<USkeletalMeshComponent>(ComponentUtils::GetAttachedParent(this));
	
	if(ParentMeshComponent)
	{
		//TODO 父类没有材质可供创建动态的时候,会崩溃
		FaceMaterialInstance = ParentMeshComponent->CreateDynamicMaterialInstance(FaceID, ParentMeshComponent->GetMaterial(FaceID),"FaceMI");
		//log
		UE_LOG(LogTemp,Warning,TEXT("UGenshinSDFComponent::RefreshFaceMaterialInstance() FaceMaterialInstance is Created"));
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

	FaceMaterialInstance->SetVectorParameterValue(FaceForwardValueName,(Forward-Head).GetSafeNormal());
	FaceMaterialInstance->SetVectorParameterValue(FaceRightValueName,(Right-Head).GetSafeNormal());
}

