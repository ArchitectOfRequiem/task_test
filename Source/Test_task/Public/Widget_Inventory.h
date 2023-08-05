// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item_Base.h"
#include "Blueprint/UserWidget.h"
#include "Widget_Inventory.generated.h"

/**
 * 
 */
UCLASS()
class TEST_TASK_API UWidget_Inventory : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(meta=(BindWidget))
	class UVerticalBox* ItemList;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UWidget_SingleItemDisplay> ItemDisplayClassRef;
	
public:
	void FeedWidgetWithItems(TArray<FItemBasicInfo>);
};
