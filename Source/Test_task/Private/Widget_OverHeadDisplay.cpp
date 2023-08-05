// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget_OverHeadDisplay.h"

#include "Widget_ResourceListing.h"

void UWidget_OverHeadDisplay::SetNewInformation(TArray<FResource> Resources)
{
	if(Widget_ResourceListing && Widget_ResourceListing->IsValidLowLevel())
	{
		Widget_ResourceListing->FeedWithResources(Resources);
	}
}
