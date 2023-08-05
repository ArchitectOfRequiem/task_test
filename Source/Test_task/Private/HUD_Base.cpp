// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD_Base.h"

#include "Character_Base.h"
#include "Widget_EscapeMenu.h"
#include "Widget_Inventory.h"
#include "Widget_MainUIDisplay.h"

void AHUD_Base::BeginPlay()
{
	Super::BeginPlay();
	
	//Create and cache escape menu
	if(EscapeMenuClassRef && EscapeMenuClassRef->IsValidLowLevel())
	{
		EscapeMenuPtr = CreateWidget<UWidget_EscapeMenu>(GetOwningPlayerController(), EscapeMenuClassRef);
	}
	//Setup MainUIDisplay
	if(MainUIDisplayClassRef && MainUIDisplayClassRef->IsValidLowLevel())
	{
		if(ACharacter_Base* Char = Cast<ACharacter_Base>(GetOwningPlayerController()->GetPawn()))
		{
			MainUIDisplayPtr = CreateWidget<UWidget_MainUIDisplay>(GetOwningPlayerController(), MainUIDisplayClassRef);
			MainUIDisplayPtr->SetNewInformation(Char->CharacterResources->GetResources());
			Char->OnResourceChange.AddUObject(MainUIDisplayPtr, &UWidget_MainUIDisplay::SetNewInformation);
			MainUIDisplayPtr->AddToViewport();
		}
	}
	
}

bool AHUD_Base::ToggleEscapeMenu()
{
	if(EscapeMenuPtr->IsInViewport())
	{
		EscapeMenuPtr->RemoveFromParent();
		return false;
	}
	else
	{
		EscapeMenuPtr->AddToViewport();
		return true;
	}
}

void AHUD_Base::SetUIVisibility(bool bVisible)
{
	if(MainUIDisplayPtr && MainUIDisplayPtr->IsValidLowLevel())
	{
		MainUIDisplayPtr->SetVisibility(bVisible ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
	}
}
