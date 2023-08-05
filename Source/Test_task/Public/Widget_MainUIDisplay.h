// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Component_Resources.h"
#include "Blueprint/UserWidget.h"
#include "Widget_MainUIDisplay.generated.h"

/**
 * 
 */
UCLASS()
class TEST_TASK_API UWidget_MainUIDisplay : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(meta=(BindWidget))
	class UWidget_ResourceListing* ResourceList;

public:
	void SetNewInformation(TArray<FResource>);
};
