// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget_SingleItemDisplay.h"

#include "Character_Base.h"
#include "Interactive_Base.h"
#include "PlayerController_Base.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

FReply UWidget_SingleItemDisplay::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	auto Reply = UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, EKeys::LeftMouseButton);
	return Reply.NativeReply;
}

void UWidget_SingleItemDisplay::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
	OutOperation = UWidgetBlueprintLibrary::CreateDragDropOperation(UDragDropOperation::StaticClass());
	OutOperation->DefaultDragVisual = this;
}

void UWidget_SingleItemDisplay::NativeOnDragCancelled(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	auto PC = GetOwningPlayer<APlayerController_Base>();
	if (PC && PC->IsValidLowLevel())
	{
		if (ACharacter_Base* Char = PC->GetPawn<ACharacter_Base>())
		{
			auto CameraComponent = Char->GetComponentByClass<UCameraComponent>();
			TArray<FHitResult> Hits;
			FVector WLoc, WDir;
			float dpis = UWidgetLayoutLibrary::GetViewportScale(GetOwningPlayer());
			FVector2D loc = UWidgetLayoutLibrary::GetMousePositionOnViewport(GetWorld()) * dpis;
			UGameplayStatics::DeprojectScreenToWorld(GetOwningPlayer(), loc, WLoc, WDir);
			
			FVector End = Char->GetActorLocation() + (500.f * WDir);
			if (UKismetSystemLibrary::SphereTraceMulti(
				GetWorld(),
				CameraComponent ? CameraComponent->GetComponentLocation() : Char->GetActorLocation(),
				End,
				40.f,
				UEngineTypes::ConvertToTraceType(ECC_Visibility),
				false,
				{Char},
				EDrawDebugTrace::Persistent,
				Hits,
				false))
			{
				for (auto Hit : Hits)
				{
					if (auto Interactive = Cast<AInteractive_Base>(Hit.GetActor()))
					{
						PC->Server_CallInteraction(Interactive, FItemBasicInfo(ItemName->GetText()));
					}
				}
			}
		}
	}
}
