// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item_Base.h"
#include "GameFramework/PlayerController.h"
#include "PlayerController_Base.generated.h"

/**
 * 
 */
UCLASS()
class TEST_TASK_API APlayerController_Base : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void SetupInputComponent() override;
	UFUNCTION() void EscapePressed();
	UFUNCTION() void LMBReactionPressed();
	void ToggleGUIVisibility(bool bDisable);

	UFUNCTION(Server, Reliable, BlueprintCallable)
	void Server_CallInteraction(class AInteractive_Base* Interactive, FItemBasicInfo Item);
	
protected:
	UFUNCTION(Server, Reliable)
	void Server_DestroyItem(class AItem_Base* Item);
	UFUNCTION(NetMulticast, Reliable)
	void Multicast_DestroyItem(AItem_Base* Item);
};
