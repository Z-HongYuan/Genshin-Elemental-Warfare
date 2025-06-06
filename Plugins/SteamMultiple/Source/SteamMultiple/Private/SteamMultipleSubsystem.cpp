// Copyright © 2025 鸿源z 保留所有权利


#include "SteamMultipleSubsystem.h"
#include "OnlineSubsystemUtils.h"

void USteamMultipleSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	if (const IOnlineSubsystem* OnlineSubsystem = Online::GetSubsystem(GetWorld()))
	{
		SessionInterface = OnlineSubsystem->GetSessionInterface();
	}

	CreateSessionCompleteDelegate = FOnCreateSessionCompleteDelegate::CreateUObject(this, &ThisClass::OnCreateSessionComplete);
	FindSessionsCompleteDelegate = FOnFindSessionsCompleteDelegate::CreateUObject(this, &ThisClass::OnFindSessionsComplete);
	JoinSessionCompleteDelegate = FOnJoinSessionCompleteDelegate::CreateUObject(this, &ThisClass::OnJoinSessionComplete);
	DestroySessionCompleteDelegate = FOnDestroySessionCompleteDelegate::CreateUObject(this, &ThisClass::OnDestroySessionComplete);
	StartSessionCompleteDelegate = FOnStartSessionCompleteDelegate::CreateUObject(this, &ThisClass::OnStartSessionComplete);
}

void USteamMultipleSubsystem::Deinitialize()
{
	if (SessionInterface.IsValid())
	{
		SessionInterface.Pin()->ClearOnCreateSessionCompleteDelegate_Handle(CreateSessionCompleteDelegateHandle);
		SessionInterface.Pin()->ClearOnFindSessionsCompleteDelegate_Handle(FindSessionsCompleteDelegateHandle);
		SessionInterface.Pin()->ClearOnJoinSessionCompleteDelegate_Handle(JoinSessionCompleteDelegateHandle);
		SessionInterface.Pin()->ClearOnDestroySessionCompleteDelegate_Handle(DestroySessionCompleteDelegateHandle);
		SessionInterface.Pin()->ClearOnStartSessionCompleteDelegate_Handle(StartSessionCompleteDelegateHandle);
		SessionInterface.Reset();
	}
	Super::Deinitialize();
}

void USteamMultipleSubsystem::CreateSession(int32 MaxConnect, FString MatchTypeStr)
{
}

void USteamMultipleSubsystem::FindSessions(int32 MaxSearchCount)
{
}

void USteamMultipleSubsystem::JoinSession(const FOnlineSessionSearchResult& SessionResult)
{
}

void USteamMultipleSubsystem::DestroySession()
{
}

void USteamMultipleSubsystem::StartSession()
{
}

void USteamMultipleSubsystem::OnCreateSessionComplete(FName SessionName, bool bWasSuccessful)
{
}

void USteamMultipleSubsystem::OnFindSessionsComplete(bool bWasSuccessful)
{
}

void USteamMultipleSubsystem::OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result)
{
}

void USteamMultipleSubsystem::OnDestroySessionComplete(FName SessionName, bool bWasSuccessful)
{
}

void USteamMultipleSubsystem::OnStartSessionComplete(FName SessionName, bool bWasSuccessful)
{
}
