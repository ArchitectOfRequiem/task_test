// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget_SingleResourceDisplay.h"

#include "Components/TextBlock.h"

FString UWidget_SingleResourceDisplay::GetStringFromEnum(EResourceType Type)
{
	switch (Type)
	{
	case EResourceType::STAMINA: return "Stamina";
	case EResourceType::HEALTH: return "Health";
	default: return "Ammunition";
	}
}

void UWidget_SingleResourceDisplay::SetupNewInformation(FResource Resource)
{
	FString InformationBuild = GetStringFromEnum(Resource.Type) + "\t" + FString::FromInt(Resource.Value);
	Information->SetText(FText::FromString(InformationBuild));
}

void UWidget_SingleResourceDisplay::SetupNewInformation(EResourceType Type, int32 Value)
{
	SetupNewInformation(FResource(Type, Value));
}
