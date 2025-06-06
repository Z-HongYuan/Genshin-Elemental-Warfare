// Copyright © 2025 鸿源z 保留所有权利

#pragma once

#include "CoreMinimal.h"
#include "OnlineSessionSettings.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "SteamMultipleSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class STEAMMULTIPLE_API USteamMultipleSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	/*
	 * 用于创建会话的函数
	 */
	UFUNCTION(BlueprintCallable)
	void CreateSession(int32 MaxConnect, FString MatchTypeStr);
	
	UFUNCTION(BlueprintCallable)
	void FindSessions(int32 MaxSearchCount);
	
	void JoinSession(const FOnlineSessionSearchResult& SessionResult);

	void DestroySession();

	void StartSession();
	
protected:
	/*
	 * 委托的回调函数
	 * 仅用于OnlineSubsystem的回调函数,不允许在其他类中使用
	 */
	void OnCreateSessionComplete(FName SessionName, bool bWasSuccessful);
	void OnFindSessionsComplete(bool bWasSuccessful);
	void OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result);
	void OnDestroySessionComplete(FName SessionName, bool bWasSuccessful);
	void OnStartSessionComplete(FName SessionName, bool bWasSuccessful);
	
	
private:
	TWeakPtr<IOnlineSession> SessionInterface;	//会话接口指针

	/*
	 * 用于添加到OnlineSubsystem的委托列表中
	 * 委托列表
	 */
	FOnCreateSessionCompleteDelegate CreateSessionCompleteDelegate;	//创建会话
	FDelegateHandle CreateSessionCompleteDelegateHandle;
	FOnFindSessionsCompleteDelegate FindSessionsCompleteDelegate;	//查找会话
	FDelegateHandle FindSessionsCompleteDelegateHandle;
	FOnJoinSessionCompleteDelegate JoinSessionCompleteDelegate;	//加入会话
	FDelegateHandle JoinSessionCompleteDelegateHandle;
	FOnDestroySessionCompleteDelegate DestroySessionCompleteDelegate;	//销毁会话
	FDelegateHandle DestroySessionCompleteDelegateHandle;
	FOnStartSessionCompleteDelegate StartSessionCompleteDelegate;	//启动会话
	FDelegateHandle StartSessionCompleteDelegateHandle;

	TWeakPtr<FOnlineSessionSettings> SessionSettings;
	
	
};
