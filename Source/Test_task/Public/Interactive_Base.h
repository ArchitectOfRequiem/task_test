// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item_Base.h"
#include "GameFramework/Actor.h"
#include "Interactive_Base.generated.h"

UCLASS()
class TEST_TASK_API AInteractive_Base : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInteractive_Base();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintImplementableEvent)
	void Interact(FItemBasicInfo Item);
};
