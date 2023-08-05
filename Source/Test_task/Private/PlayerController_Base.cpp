// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerController_Base.h"

#include "Character_Base.h"
#include "Component_Inventory.h"
#include "EngineUtils.h"
#include "HUD_Base.h"
#include "Interactive_Base.h"
#include "Item_Base.h"
#include "Camera/CameraComponent.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"

void APlayerController_Base::SetupInputComponent()
{
	Super::SetupInputComponent();
	
	InputComponent->BindAction(FName("EscapeButton"), EInputEvent::IE_Pressed, this, &APlayerController_Base::EscapePressed);
	InputComponent->BindAction(FName("LMBReaction"), EInputEvent::IE_Pressed, this, &APlayerController_Base::LMBReactionPressed);
}

void APlayerController_Base::EscapePressed()
{
	bool bMenuIsOpen = GetHUD<AHUD_Base>()->ToggleEscapeMenu();
	
	SetShowMouseCursor(bMenuIsOpen);
	
	bMenuIsOpen ? GetPawn()->DisableInput(this) : GetPawn()->EnableInput(this);
	GetPawn()->CustomTimeDilation = bMenuIsOpen ? 0.0001f : 1.f;
	
	ToggleGUIVisibility(bMenuIsOpen);
	GetHUD<AHUD_Base>()->SetUIVisibility(!bMenuIsOpen);
}

void APlayerController_Base::LMBReactionPressed()
{
	if(ACharacter_Base* Char = GetPawn<ACharacter_Base>())
	{
		auto CameraComponent = Char->GetComponentByClass<UCameraComponent>();
		if(Char->Inventory->IsInventoryOpen() && CameraComponent && CameraComponent->IsValidLowLevel())
		{
			FVector WLoc, WDir;
			if(DeprojectMousePositionToWorld(WLoc, WDir))
			{
				FVector End = FVector(CameraComponent->GetComponentLocation() + (WDir * 1000.f));
				TArray<FHitResult> Hits;
				
				if(UKismetSystemLibrary::SphereTraceMulti(
					GetWorld(),
					CameraComponent->GetComponentLocation(),
					End,
					40.f,
					UEngineTypes::ConvertToTraceType(ECollisionChannel::ECC_Visibility),
					false,
					{GetOwner()},
					EDrawDebugTrace::Persistent,
					Hits,
					true))
				{
					for(auto Hit : Hits)
					{
						if(AItem_Base* Item = Cast<AItem_Base>(Hit.GetActor()))
						{
							Char->Inventory->AddNewItem(Item->GetBasicInfo());
							Server_DestroyItem(Item);
							break;
						}
					}
				}
			}
		}
	}
}

void APlayerController_Base::ToggleGUIVisibility(bool bDisable)
{
	for(TActorIterator<ACharacter_Base> It(GetWorld()); It; ++It)
	{
		if(It->ResourceDisplay && It->ResourceDisplay->IsValidLowLevel())
			It->ResourceDisplay->SetVisibility(!bDisable);
	}
}

void APlayerController_Base::Server_CallInteraction_Implementation(AInteractive_Base* Interactive, FItemBasicInfo Item)
{
	Interactive->Interact(Item);
}

void APlayerController_Base::Server_DestroyItem_Implementation(AItem_Base* Item)
{
	Multicast_DestroyItem(Item);
}

void APlayerController_Base::Multicast_DestroyItem_Implementation(AItem_Base* Item)
{
	if(!IsValid(Item)) return;
	Item->Destroy();
}
