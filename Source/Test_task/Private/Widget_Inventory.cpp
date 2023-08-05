// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget_Inventory.h"

#include "Widget_SingleItemDisplay.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"

void UWidget_Inventory::FeedWidgetWithItems(TArray<FItemBasicInfo> Items)
{
	if(!ItemDisplayClassRef || !ItemDisplayClassRef->IsValidLowLevel()) return;
	
	ItemList->ClearChildren();
	for(auto Item : Items)
	{
		auto SingleItemWidget = CreateWidget<UWidget_SingleItemDisplay>(GetOwningPlayer(), ItemDisplayClassRef);
		if(SingleItemWidget)
		{
			SingleItemWidget->ItemName->SetText(Item.ItemName.IsEmpty()? FText::FromString("Empty Slot") : Item.ItemName);
			
			ItemList->AddChildToVerticalBox(SingleItemWidget);
		}
	}
}

