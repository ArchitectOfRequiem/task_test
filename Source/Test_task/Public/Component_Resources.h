// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Component_Resources.generated.h"



UENUM()
enum class EResourceType : uint8
{
	STAMINA = 0,
	HEALTH,
	AMMUNITION
};
ENUM_RANGE_BY_FIRST_AND_LAST(EResourceType, EResourceType::STAMINA, EResourceType::AMMUNITION);

USTRUCT()
struct FResource
{
	GENERATED_BODY()
	FResource() = default;
	FResource(EResourceType _Type, int32 _Value) : Type(_Type), Value(_Value) {};
	
	UPROPERTY(VisibleAnywhere) EResourceType Type = EResourceType::HEALTH;
	UPROPERTY(VisibleAnywhere) int32 Value = 0;
};

DECLARE_EVENT(UComponent_Resources, FOnResourceChange);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TEST_TASK_API UComponent_Resources : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UComponent_Resources();
	
	FOnResourceChange OnResourcesChange;
	
protected:
	UPROPERTY(EditAnywhere)
	TMap<EResourceType, int32> StartingResources;

	UPROPERTY(VisibleAnywhere, Replicated, ReplicatedUsing=OnRep_Resources)
	TArray<FResource> Resources;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void PostLoad() override;

public:
	TArray<FResource> GetResources() const { return this->Resources; }
	void SetNewValueFor(EResourceType Type, int32 Value);
	int32 GetValueOf(EResourceType Type) const;
	
	UFUNCTION()
	void OnRep_Resources();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
