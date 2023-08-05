// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Item_Base.generated.h"

USTRUCT(BlueprintType)
struct FItemBasicInfo
{
	GENERATED_BODY()
	FItemBasicInfo() = default;
	FItemBasicInfo(const FText& _Name) : ItemName(_Name){};

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite) FText ItemName = FText::GetEmpty();
};

UCLASS()
class TEST_TASK_API AItem_Base : public AActor
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	AItem_Base();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FItemBasicInfo BasicInfo;

public:
	FItemBasicInfo& GetBasicInfo() { return this->BasicInfo;}
};