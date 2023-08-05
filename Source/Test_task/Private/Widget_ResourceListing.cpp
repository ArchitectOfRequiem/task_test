// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget_ResourceListing.h"

#include "Widget_SingleResourceDisplay.h"
#include "Components/VerticalBox.h"

void UWidget_ResourceListing::FeedWithResources(TArray<FResource> Resources)
{
	if(ResourceClassToDisplay && ResourceClassToDisplay->IsValidLowLevel())
	{
		ResourceList->ClearChildren();
		for(const auto& Resource : Resources)
		{
			auto Widget = CreateWidget<UWidget_SingleResourceDisplay>(GetOwningPlayer(), ResourceClassToDisplay);
			if(Widget && Widget->IsValidLowLevel())
			{
				Widget->SetupNewInformation(Resource);
				ResourceList->AddChildToVerticalBox(Widget);
			}
		}
	}
	
}
