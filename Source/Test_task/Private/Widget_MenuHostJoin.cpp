// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget_MenuHostJoin.h"

#include "GISS_Networking.h"
#include "Components/Button.h"

void UWidget_MenuHostJoin::NativeConstruct()
{
	Super::NativeConstruct();
	GetPlayerContext().GetPlayerController()->SetShowMouseCursor(true);
	GetGameInstance()->GetSubsystem<UGISS_Networking>()->OnFindSessionFinish.AddUObject(this, &UWidget_MenuHostJoin::OnFindSessionFinish);
	Host->OnClicked.AddUniqueDynamic(this, &UWidget_MenuHostJoin::OnHostClicked);
	Join->OnClicked.AddUniqueDynamic(this, &UWidget_MenuHostJoin::OnJoinClicked);
}

void UWidget_MenuHostJoin::OnHostClicked()
{
	GetGameInstance()->GetSubsystem<UGISS_Networking>()->HostSession(GetPlayerContext().GetLocalPlayer()->GetPreferredUniqueNetId().GetUniqueNetId());
}

void UWidget_MenuHostJoin::OnJoinClicked()
{
	GetGameInstance()->GetSubsystem<UGISS_Networking>()->FindSessions(GetPlayerContext().GetLocalPlayer()->GetPreferredUniqueNetId().GetUniqueNetId());
}

void UWidget_MenuHostJoin::OnFindSessionFinish()
{
	GetGameInstance()->GetSubsystem<UGISS_Networking>()->JoinSession(GetPlayerContext().GetLocalPlayer()->GetPreferredUniqueNetId().GetUniqueNetId());
}
