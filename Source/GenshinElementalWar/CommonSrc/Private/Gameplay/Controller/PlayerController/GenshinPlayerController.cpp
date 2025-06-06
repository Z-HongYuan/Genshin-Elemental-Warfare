// Copyright © 2025 鸿源z 保留所有权利


#include "GenshinElementalWar/CommonSrc/Public/Gameplay/Controller/PlayerController/GenshinPlayerController.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "GenshinElementalWar/CommonSrc/Public/CameraSystem/PlayerCameraManager/GenshinPlayerCameraManager.h"
#include "GenshinElementalWar/CommonSrc/Public/InputSystem/GenshinEnhancedInputComponent.h"
#include "GenshinElementalWar/CommonSrc/Public/Misc/CheatManager/GenshinCheatManager.h"


AGenshinPlayerController::AGenshinPlayerController()
{
	bReplicates = true;	//启动复制
	
	PlayerCameraManagerClass = AGenshinPlayerCameraManager::StaticClass();
	CheatClass= UGenshinCheatManager::StaticClass();
	
	bAutoManageActiveCameraTarget = false;
}

void AGenshinPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (IsLocalController())	//在本地控制器中添加Mapping
	{
		if(UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultContext,0);
			SetInputMode(FInputModeGameOnly());
		}
		else
		{
			UE_LOG(LogTemp,Warning,TEXT("AGenshinPlayerController::BeginPlay() UEnhancedInputLocalPlayerSubsystem is nullptr"));
		}
	}
}

void AGenshinPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (IsLocalController())	//在本地控制器中添加Bind
	{
		if (UGenshinEnhancedInputComponent* GenshinEnhancedInput = CastChecked<UGenshinEnhancedInputComponent>(InputComponent))
		{
			GenshinEnhancedInput->BindAction(
			   MoveAction,
			   ETriggerEvent::Triggered,
			   this,
			   &AGenshinPlayerController::HandleMove
			   );

			GenshinEnhancedInput->BindAction(
				LookAction, 
				ETriggerEvent::Triggered,
				this,
				&AGenshinPlayerController::HandleLook
				);

			GenshinEnhancedInput->BindAbilityAction(
				InputDataAsset,
				this,
				&ThisClass::AbilityInputTagPressed,
				&ThisClass::AbilityInputTagReleased,
				&ThisClass::AbilityInputTagHeld);
		}
		else
		{
			UE_LOG(LogTemp,Warning,TEXT("UGenshinPlayerController::SetupInputComponent() UGenshinEnhancedInputComponent is nullptr"));
		}
	}
}

void AGenshinPlayerController::HandleMove(const FInputActionValue& Value) 
{
	const FVector2D MovementVector = Value.Get<FVector2D>();
	if (APawn* ControlledPawn = GetPawn())
	{
		const FRotator Rotation = GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// 从控制旋转中提取出Forward和Right方向
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		ControlledPawn->AddMovementInput(ForwardDirection, MovementVector.Y);
		ControlledPawn->AddMovementInput(RightDirection, MovementVector.X);
	}
}

void AGenshinPlayerController::HandleLook(const FInputActionValue& Value)
{
	const FVector2D LookVector = Value.Get<FVector2D>();
	AddPitchInput(LookVector.Y * UpDownRate);
	AddYawInput(LookVector.X * LeftRightRate);
}

void AGenshinPlayerController::AbilityInputTagPressed(FGameplayTag InputTag)
{
	// GetASC()->
	// 在ASC中,Held处理了激活一次Ability的能力,所有可以观望一下是否需要Pressed
}

void AGenshinPlayerController::AbilityInputTagReleased(FGameplayTag InputTag)
{
	if (GetASC()==nullptr) return;
	GetASC()->AbilityInputTagReleased(InputTag);
}

void AGenshinPlayerController::AbilityInputTagHeld(FGameplayTag InputTag)
{
	if (GetASC()==nullptr) return;
	GetASC()->AbilityInputTagHeld(InputTag);
}

UGenshinAbilitySystemComponent* AGenshinPlayerController::GetASC()
{
	if (GenshinAbilitySystemComponent==nullptr or !GenshinAbilitySystemComponent.IsValid())
	{
		GenshinAbilitySystemComponent=Cast<UGenshinAbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetPawn()));
	}
	return GenshinAbilitySystemComponent.Get();
}

