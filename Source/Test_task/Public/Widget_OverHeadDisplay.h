// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Component_Resources.h"
#include "Blueprint/UserWidget.h"
#include "Widget_OverHeadDisplay.generated.h"

/**
 * 
 */
UCLASS()
class TEST_TASK_API UWidget_OverHeadDisplay : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(meta=(BindWidget))
	class UWidget_ResourceListing* Widget_ResourceListing;

public:
	UFUNCTION()
	void SetNewInformation(TArray<FResource> Resources);
};
