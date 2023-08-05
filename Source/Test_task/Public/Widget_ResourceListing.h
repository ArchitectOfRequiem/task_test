// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Component_Resources.h"
#include "Blueprint/UserWidget.h"
#include "Widget_ResourceListing.generated.h"

/**
 * 
 */
UCLASS()
class TEST_TASK_API UWidget_ResourceListing : public UUserWidget
{
	GENERATED_BODY()
protected:
	UPROPERTY(meta=(BindWidget))
	class UVerticalBox* ResourceList;
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UWidget_SingleResourceDisplay> ResourceClassToDisplay;
	
public:
	void FeedWithResources(TArray<FResource> Resources);
};
