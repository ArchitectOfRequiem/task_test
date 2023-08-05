// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item_Base.h"
#include "Components/ActorComponent.h"
#include "Component_Inventory.generated.h"

DECLARE_EVENT_OneParam(UComponent_Inventory, FOnInventoryChange, TArray<FItemBasicInfo>);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class TEST_TASK_API UComponent_Inventory : public UActorComponent
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UWidget_Inventory> WidgetInventoryClassRef;
	UPROPERTY()
	UWidget_Inventory* WidgetInventoryPtr = nullptr;
	
public:
	// Sets default values for this component's properties
	UComponent_Inventory();

	FOnInventoryChange OnInventoryChange;

	UPROPERTY(EditDefaultsOnly)
	uint32 InventorySlots = 1;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

    UPROPERTY()
	TArray<FItemBasicInfo> Items;
	
public:

	bool ToggleInventoryWidget();
	bool IsInventoryOpen() const;
	
	bool AddNewItem(const FItemBasicInfo& NewItem);
};
