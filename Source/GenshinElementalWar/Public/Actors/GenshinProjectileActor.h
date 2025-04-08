// Copyright © 2025 鸿源z 保留所有权利

#pragma once

#include "CoreMinimal.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "GenshinProjectileActor.generated.h"

UCLASS()
class GENSHINELEMENTALWAR_API AGenshinProjectileActor : public AActor
{
	GENERATED_BODY()

public:
	AGenshinProjectileActor();

	//TODO 应用GE到碰撞的Pawn
	UFUNCTION(BlueprintCallable, Category = "Projectile")
	void ApplyEffectToOverlap(AActor* ApplyActor,bool bIgnorePlayer);
protected:
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ProjectileMesh")
	TObjectPtr<UStaticMeshComponent> ProjectileMesh;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "CapsuleComponent")
	TObjectPtr<UCapsuleComponent> CapsuleComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ProjectileMovementComponent")
	TObjectPtr<UProjectileMovementComponent> ProjectileMovementComponent;
	
public:
	virtual void Tick(float DeltaTime) override;
};
