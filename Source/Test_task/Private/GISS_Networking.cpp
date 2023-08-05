// Fill out your copyright notice in the Description page of Project Settings.


#include "GISS_Networking.h"

#include "OnlineSessionSettings.h"
#include "OnlineSubsystem.h"
#include "PlayerController_Base.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "Kismet/GameplayStatics.h"
#include "Online/OnlineSessionNames.h"

void UGISS_Networking::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	OnCreateSessionCompleteDelegate = FOnCreateSessionCompleteDelegate::CreateUObject(this, &UGISS_Networking::OnCreateSessionComplete);
	OnStartSessionCompleteDelegate = FOnCreateSessionCompleteDelegate::CreateUObject(this, &UGISS_Networking::OnStartOnlineGameComplete);

	OnFindSessionsCompleteDelegate = FOnFindSessionsCompleteDelegate::CreateUObject(this, &UGISS_Networking::OnFindSession);

	OnJoinSessionCompleteDelegate = FOnJoinSessionCompleteDelegate::CreateUObject(this, &UGISS_Networking::OnJoinSessionComplete);

	OnDestroySessionCompleteDelegate = FOnDestroySessionCompleteDelegate::CreateUObject(this, &UGISS_Networking::OnDestroySessionComplete);
}

void UGISS_Networking::Deinitialize()
{
	IOnlineSubsystem* OnlineSubsystem = IOnlineSubsystem::Get();
	if(OnlineSubsystem)
	{
		IOnlineSessionPtr Session = OnlineSubsystem->GetSessionInterface();
		if(Session.IsValid())
		{
			Session->AddOnDestroySessionCompleteDelegate_Handle(OnDestroySessionCompleteDelegate);
			Session->DestroySession(FName("Test_task"));
		}
	}
	Super::Deinitialize();
}

void UGISS_Networking::HostSession(TSharedPtr<const FUniqueNetId> UserNetId)
{
	IOnlineSubsystem* OnlineSubsystem = IOnlineSubsystem::Get();
	if (OnlineSubsystem)
	{
		IOnlineSessionPtr Session = OnlineSubsystem->GetSessionInterface();
		if (Session.IsValid() && UserNetId.IsValid())
		{
			SessionSettings = MakeShareable(new FOnlineSessionSettings());

			SessionSettings->bIsLANMatch = true;
			SessionSettings->bUsesPresence = true;
			SessionSettings->NumPublicConnections = 4;
			SessionSettings->bAllowJoinInProgress = true;
			SessionSettings->bShouldAdvertise = true;
			SessionSettings->bAllowJoinViaPresence = true;
			SessionSettings->bAllowJoinViaPresenceFriendsOnly = false;

			SessionSettings->Set(SETTING_MAPNAME, FString("ThirdPersonMap"), EOnlineDataAdvertisementType::ViaOnlineService);
			OnCreateSessionCompleteDelegateHandle = Session->AddOnCreateSessionCompleteDelegate_Handle(OnCreateSessionCompleteDelegate);
			FName SessionName(TEXT("Test_task"));
			Session->CreateSession(*UserNetId, SessionName, *SessionSettings);
		}
	}
}


void UGISS_Networking::OnCreateSessionComplete(FName SessionName, bool bSuccess)
{
	IOnlineSubsystem* OnlineSubsystem = IOnlineSubsystem::Get();
	if (OnlineSubsystem)
	{
		IOnlineSessionPtr Session = OnlineSubsystem->GetSessionInterface();
		if (Session.IsValid())
		{
			Session->ClearOnCreateSessionCompleteDelegate_Handle(OnCreateSessionCompleteDelegateHandle);
			if (bSuccess)
			{
				OnStartSessionCompleteDelegateHandle = Session->AddOnStartSessionCompleteDelegate_Handle(OnStartSessionCompleteDelegate);
				Session->StartSession(SessionName);
			}
		}
	}
}

void UGISS_Networking::OnStartOnlineGameComplete(FName SessionName, bool bSuccess)
{
	IOnlineSubsystem* OnlineSubsystem = IOnlineSubsystem::Get();
	if (OnlineSubsystem)
	{
		IOnlineSessionPtr Session = OnlineSubsystem->GetSessionInterface();
		if (Session.IsValid())
		{
			Session->ClearOnStartSessionCompleteDelegate_Handle(OnStartSessionCompleteDelegateHandle);
		}
	}
	if (bSuccess)
	{
		UGameplayStatics::OpenLevel(GetWorld(), "ThirdPersonMap", true, "listen");
	}
}

void UGISS_Networking::FindSessions(TSharedPtr<const FUniqueNetId> UserNetId)
{
	IOnlineSubsystem* OnlineSubsystem = IOnlineSubsystem::Get();
	if (OnlineSubsystem)
	{
		IOnlineSessionPtr Session = OnlineSubsystem->GetSessionInterface();
		if (Session.IsValid() && UserNetId.IsValid())
		{
			SessionSearchSettings = MakeShareable(new FOnlineSessionSearch());

			SessionSearchSettings->bIsLanQuery = true;
			SessionSearchSettings->MaxSearchResults = 50;
			SessionSearchSettings->PingBucketSize = 200;
			SessionSearchSettings->QuerySettings.Set(SEARCH_PRESENCE, true, EOnlineComparisonOp::Equals);

			OnFindSessionsCompleteDelegateHandle = Session->AddOnFindSessionsCompleteDelegate_Handle(OnFindSessionsCompleteDelegate);
			Session->FindSessions(*UserNetId, SessionSearchSettings.ToSharedRef());
		}
	}
}


void UGISS_Networking::OnFindSession(bool bSuccess)
{
	IOnlineSubsystem* OnlineSubsystem = IOnlineSubsystem::Get();
	if (OnlineSubsystem)
	{
		IOnlineSessionPtr Session = OnlineSubsystem->GetSessionInterface();
		if (Session.IsValid())
		{
			Session->ClearOnFindSessionsCompleteDelegate_Handle(OnFindSessionsCompleteDelegateHandle);
		}
	}

	if(bSuccess)
	{
		OnFindSessionFinish.Broadcast();
	}
}


void UGISS_Networking::JoinSession(TSharedPtr<const FUniqueNetId> UserNetId)
{
	IOnlineSubsystem* OnlineSubsystem = IOnlineSubsystem::Get();
	if (OnlineSubsystem)
	{
		IOnlineSessionPtr Session = OnlineSubsystem->GetSessionInterface();
		if (Session.IsValid() && UserNetId.IsValid() && SessionSearchSettings->SearchResults.IsValidIndex(0))
		{
			OnJoinSessionCompleteDelegateHandle = Session->AddOnJoinSessionCompleteDelegate_Handle(OnJoinSessionCompleteDelegate);
			Session->JoinSession(*UserNetId, FName("Test_task"), SessionSearchSettings->SearchResults[0]);
		}
	}
}

void UGISS_Networking::OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result)
{
	IOnlineSubsystem* OnlineSubsystem = IOnlineSubsystem::Get();
	if (OnlineSubsystem)
	{
		IOnlineSessionPtr Session = OnlineSubsystem->GetSessionInterface();
		if (Session.IsValid())
		{
			Session->ClearOnJoinSessionCompleteDelegate_Handle(OnJoinSessionCompleteDelegateHandle);
			APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
			if (PC && PC->IsValidLowLevel())
			{
				FString URL;
				if (Session->GetResolvedConnectString(SessionName, URL))
				{
					PC->ClientTravel(URL, ETravelType::TRAVEL_Absolute, false);
				}
			}
		}
	}
}

void UGISS_Networking::OnDestroySessionComplete(FName SessionName, bool bSuccess)
{
	IOnlineSubsystem* OnlineSubsystem = IOnlineSubsystem::Get();
	if (OnlineSubsystem)
	{
		IOnlineSessionPtr Session = OnlineSubsystem->GetSessionInterface();

		if (Session.IsValid())
		{
			Session->ClearOnDestroySessionCompleteDelegate_Handle(OnDestroySessionCompleteDelegateHandle);
			if (bSuccess)
			{
				UGameplayStatics::OpenLevel(GetWorld(), "Entry", true);
			}
		}
	}
}
