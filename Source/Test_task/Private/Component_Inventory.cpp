// Fill out your copyright notice in the Description page of Project Settings.


#include "Component_Inventory.h"
#include "Widget_Inventory.h"
#include "Kismet/GameplayStatics.h"


// Sets default values for this component's properties
UComponent_Inventory::UComponent_Inventory()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UComponent_Inventory::BeginPlay()
{
	Super::BeginPlay();

	// ...
	Items.Init(FItemBasicInfo(), InventorySlots);
	if(WidgetInventoryClassRef && WidgetInventoryClassRef->IsValidLowLevel())
	{
		WidgetInventoryPtr = CreateWidget<UWidget_Inventory>(UGameplayStatics::GetPlayerController(GetWorld(), 0), WidgetInventoryClassRef);
		if(WidgetInventoryPtr)
		{
			WidgetInventoryPtr->FeedWidgetWithItems(Items);
			OnInventoryChange.AddUObject(WidgetInventoryPtr, &UWidget_Inventory::FeedWidgetWithItems);
		}
	}
}



bool UComponent_Inventory::ToggleInventoryWidget()
{
	if(!WidgetInventoryPtr) return false;
	auto PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	if(WidgetInventoryPtr->IsInViewport())
	{
		PC->SetShowMouseCursor(false);
		WidgetInventoryPtr->RemoveFromParent();
		return false;
	}
	else
	{
		PC->SetShowMouseCursor(true);
		WidgetInventoryPtr->AddToViewport();
		return true;
	}
}

bool UComponent_Inventory::IsInventoryOpen() const
{
	return WidgetInventoryPtr && WidgetInventoryPtr->IsInViewport();
}

bool UComponent_Inventory::AddNewItem(const FItemBasicInfo& NewItem)
{
	auto FreeSlotPtr = Items.FindByPredicate([](const FItemBasicInfo& Element)
	{
		return Element.ItemName.IsEmpty();
	});
	if(FreeSlotPtr)
	{
		*FreeSlotPtr = NewItem;
		OnInventoryChange.Broadcast(Items);
		return true;
	}

	return false;
}
