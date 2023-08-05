// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Widget_EscapeMenu.generated.h"

/**
 * 
 */
UCLASS()
class TEST_TASK_API UWidget_EscapeMenu : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY()
	class UWidget_Options* OptionsPtr;
	
public:
	virtual void NativeConstruct() override;
	virtual void RemoveFromParent() override;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<UWidget_Options> OptionsClassRef;
	
protected:
	UPROPERTY(meta=(BindWidget))
	class UButton* OptionMenu;

	UPROPERTY(meta=(BindWidget))
	UButton* ExitEscapeMenu;

	UFUNCTION()
	void OnExitClicked();

	UFUNCTION()
	void OnOptionsMenuClicked();
};
