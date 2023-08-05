// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interfaces/OnlineSessionDelegates.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Online.h"
#include "OnlineSessionSettings.h"

#include "GISS_Networking.generated.h"

/**
 * I stick to Host and Join first found session only, session contains up to 4 players
 */

DECLARE_EVENT(UGISS_Networking, FOnSessionFindFinish);

UCLASS(BlueprintType)
class TEST_TASK_API UGISS_Networking : public UGameInstanceSubsystem
{
	GENERATED_BODY()

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	
	FOnCreateSessionCompleteDelegate OnCreateSessionCompleteDelegate;
	FOnStartSessionCompleteDelegate OnStartSessionCompleteDelegate;
	FDelegateHandle OnCreateSessionCompleteDelegateHandle;
	FDelegateHandle OnStartSessionCompleteDelegateHandle;
	
	FOnFindSessionsCompleteDelegate OnFindSessionsCompleteDelegate;
	FDelegateHandle OnFindSessionsCompleteDelegateHandle;
	
	FOnJoinSessionCompleteDelegate OnJoinSessionCompleteDelegate;
	FDelegateHandle OnJoinSessionCompleteDelegateHandle;
	
	FOnDestroySessionCompleteDelegate OnDestroySessionCompleteDelegate;
	FDelegateHandle OnDestroySessionCompleteDelegateHandle;

	TSharedPtr<FOnlineSessionSettings> SessionSettings;
	TSharedPtr<FOnlineSessionSearch> SessionSearchSettings;
public:
	FOnSessionFindFinish OnFindSessionFinish;
	
	void HostSession(TSharedPtr<const FUniqueNetId> UserNetId);
	void FindSessions(TSharedPtr<const FUniqueNetId> UserNetId);
	void JoinSession(TSharedPtr<const FUniqueNetId> UserNetId);
protected:
	void OnCreateSessionComplete(FName SessionName, bool bSuccess);
	void OnStartOnlineGameComplete(FName SessionName, bool bSuccess);

	void OnFindSession(bool bSuccess);

	void OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result);
	
	virtual void OnDestroySessionComplete(FName SessionName, bool bSuccess);
};


