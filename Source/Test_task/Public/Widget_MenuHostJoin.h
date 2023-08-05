// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Widget_MenuHostJoin.generated.h"

/**
 * 
 */
UCLASS()
class TEST_TASK_API UWidget_MenuHostJoin : public UUserWidget
{
	GENERATED_BODY()
	
	UPROPERTY(meta=(BindWidget))
	class UButton* Host;

	UPROPERTY(meta=(BindWidget))
	UButton* Join;
	
public:
	virtual void NativeConstruct() override;
	
	UFUNCTION() void OnHostClicked();
	UFUNCTION() void OnJoinClicked();

protected:
	void OnFindSessionFinish();
};
