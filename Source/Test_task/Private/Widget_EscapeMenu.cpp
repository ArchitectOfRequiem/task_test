// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget_EscapeMenu.h"

#include "HUD_Base.h"
#include "PlayerController_Base.h"
#include "Widget_Options.h"
#include "Components/Button.h"

void UWidget_EscapeMenu::NativeConstruct()
{
	Super::NativeConstruct();

	if(OptionsClassRef && OptionsClassRef->IsValidLowLevel())
	{
		OptionsPtr = CreateWidget<UWidget_Options>(GetPlayerContext().GetPlayerController(), OptionsClassRef);
	}
	
	OptionMenu->OnClicked.AddUniqueDynamic(this, &UWidget_EscapeMenu::OnOptionsMenuClicked);
	ExitEscapeMenu->OnClicked.AddUniqueDynamic(this, &UWidget_EscapeMenu::OnExitClicked);
}

void UWidget_EscapeMenu::RemoveFromParent()
{
	Super::RemoveFromParent();

	if(OptionsPtr && OptionsPtr->IsValidLowLevel()) OptionsPtr->RemoveFromParent();
}

void UWidget_EscapeMenu::OnExitClicked()
{
	GetPlayerContext().GetPlayerController<APlayerController_Base>()->EscapePressed();
}

void UWidget_EscapeMenu::OnOptionsMenuClicked()
{
	OptionsPtr->IsInViewport() ? OptionsPtr->RemoveFromParent() : OptionsPtr->AddToViewport();
}
