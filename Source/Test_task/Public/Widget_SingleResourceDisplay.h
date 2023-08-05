// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Component_Resources.h"
#include "Blueprint/UserWidget.h"
#include "Widget_SingleResourceDisplay.generated.h"

/**
 * 
 */
UCLASS()
class TEST_TASK_API UWidget_SingleResourceDisplay : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta=(BindWidget))
	class UTextBlock* Information;

	FString GetStringFromEnum(EResourceType Type);
public:
	void SetupNewInformation(FResource Resource);
	void SetupNewInformation(EResourceType Type, int32 Value);
};
