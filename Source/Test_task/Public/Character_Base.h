// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Component_Resources.h"
#include "GameFramework/Character.h"
#include "Character_Base.generated.h"

USTRUCT(BlueprintType)
struct FStaminaConfig
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite) int32 RechargeAmount = 5;
	UPROPERTY(BlueprintReadWrite) float RechargeInterval = 1.f;
};


DECLARE_EVENT_OneParam(ACharacter_Base, FOnResourceChanges, TArray<FResource>);

UCLASS()
class TEST_TASK_API ACharacter_Base : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACharacter_Base();

	UPROPERTY(VisibleAnywhere)
	class UComponent_Resources* CharacterResources;

	UPROPERTY(VisibleAnywhere)
	class UWidgetComponent* ResourceDisplay;

	UPROPERTY(VisibleAnywhere)
	class UComponent_Inventory* Inventory;

	FOnResourceChanges OnResourceChange;
protected:
	FStaminaConfig StaminaConfig; //Done for "any option in option menu"
	
	bool bIsRunning = false;
	
	FTimerHandle RunningDelayRechargeTimerHandle;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()	void OnResourcesChange();
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
	void ToggleInventory();
	
	UFUNCTION()
	void OnFire();

	UFUNCTION()
	void Run(float val);

	UFUNCTION()
	void StartRun();

	UFUNCTION()
	void StopRun();

	UFUNCTION(BlueprintCallable, Server, Reliable)
	void SetNewValueForResource(EResourceType Type, int32 Value);

	UFUNCTION(BlueprintPure)
	int32 GetValueFor(EResourceType Type);

	UFUNCTION(BlueprintCallable)
	void SetNewStaminaConfig(FStaminaConfig NewStaminaConfig);

	UFUNCTION(BlueprintPure)
	FStaminaConfig GetStaminaConfig() const {return this->StaminaConfig;}
};

