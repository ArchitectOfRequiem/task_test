// Fill out your copyright notice in the Description page of Project Settings.


#include "Component_Resources.h"

#include "Net/UnrealNetwork.h"

// Sets default values for this component's properties
UComponent_Resources::UComponent_Resources()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	SetIsReplicatedByDefault(true);
	// ...

	for(auto ResourceType : TEnumRange<EResourceType>())
	{
		if(ResourceType == EResourceType::AMMUNITION)
		{
			StartingResources.Add(ResourceType, 30);
			continue;
		}
		StartingResources.Add(ResourceType, 100);
	}
}


// Called when the game starts
void UComponent_Resources::BeginPlay()
{
	Super::BeginPlay();
	// ...
}

void UComponent_Resources::PostLoad()
{
	Super::PostLoad();
	for(const auto& StartingResource : StartingResources)
	{
		Resources.Add(FResource(StartingResource.Key, StartingResource.Value));
	}
	StartingResources.Empty(); //No need to keep memory for starting resources, just release it
}

void UComponent_Resources::SetNewValueFor(EResourceType Type, int32 Value)
{
	for(auto& Resource : Resources)
	{
		if(Resource.Type == Type)
		{
			Resource.Value = FMath::Clamp(Value, 0, INT_MAX);
			OnRep_Resources(); //Called for server
			break;
		}
	}
}


int32 UComponent_Resources::GetValueOf(EResourceType Type) const
{
	for(const auto& Resource : Resources)
	{
		if(Resource.Type == Type) return Resource.Value;
	}

	return -1;
}

void UComponent_Resources::OnRep_Resources()
{
	OnResourcesChange.Broadcast();
}

void UComponent_Resources::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(UComponent_Resources, Resources);
}



