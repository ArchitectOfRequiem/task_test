// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget_MainUIDisplay.h"

#include "Widget_ResourceListing.h"

void UWidget_MainUIDisplay::SetNewInformation(TArray<FResource> Resources)
{
	ResourceList->FeedWithResources(Resources);
}
