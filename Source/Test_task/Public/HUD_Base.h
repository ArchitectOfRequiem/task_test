// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "HUD_Base.generated.h"

/**
 * 
 */
UCLASS()
class TEST_TASK_API AHUD_Base : public AHUD
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UWidget_EscapeMenu> EscapeMenuClassRef;
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UWidget_MainUIDisplay> MainUIDisplayClassRef;
	
	UPROPERTY()
	UWidget_EscapeMenu* EscapeMenuPtr = nullptr;
	UPROPERTY()
	UWidget_MainUIDisplay* MainUIDisplayPtr = nullptr;

	virtual void BeginPlay() override;
public:
	bool ToggleEscapeMenu();
	
	void SetUIVisibility(bool bVisible);
	
};
