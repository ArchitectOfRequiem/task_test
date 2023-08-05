// Fill out your copyright notice in the Description page of Project Settings.


#include "Character_Base.h"

#include "Component_Inventory.h"
#include "Component_Resources.h"
#include "Widget_OverHeadDisplay.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/PawnMovementComponent.h"

// Sets default values
ACharacter_Base::ACharacter_Base()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;

	CharacterResources = CreateDefaultSubobject<UComponent_Resources>(TEXT("Resources Manager"));
	CharacterResources->SetIsReplicated(true);

	Inventory = CreateDefaultSubobject<UComponent_Inventory>(TEXT("Inventory"));
	
	ResourceDisplay = CreateDefaultSubobject<UWidgetComponent>(TEXT("Resource Display"));
	ResourceDisplay->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ACharacter_Base::BeginPlay()
{
	Super::BeginPlay();
	CharacterResources->OnResourcesChange.AddUFunction(this, FName("OnResourcesChange"));
	
	if(IsLocallyControlled())
	{
		ResourceDisplay->Deactivate();
		ResourceDisplay = nullptr;
	}
	else if(UWidget_OverHeadDisplay* Widget = Cast<UWidget_OverHeadDisplay>(ResourceDisplay->GetWidget()))
	{
		Widget->SetNewInformation(CharacterResources->GetResources());
		OnResourceChange.AddUFunction(Widget, TEXT("SetNewInformation"));
	}
}

void ACharacter_Base::OnResourcesChange()
{
	OnResourceChange.Broadcast(CharacterResources->GetResources());
}

// Called every frame
void ACharacter_Base::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ACharacter_Base::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction(FName("Fire"), EInputEvent::IE_Pressed, this, &ACharacter_Base::OnFire);
	PlayerInputComponent->BindAction(FName("RunAction"), EInputEvent::IE_Pressed, this, &ACharacter_Base::StartRun);
	PlayerInputComponent->BindAction(FName("RunAction"), EInputEvent::IE_Released, this, &ACharacter_Base::StopRun);
	PlayerInputComponent->BindAction(FName("InventoryToggle"), EInputEvent::IE_Pressed, this, &ACharacter_Base::ToggleInventory);
	
	PlayerInputComponent->BindAxis(FName("Run"), this, &ACharacter_Base::Run);
}

void ACharacter_Base::ToggleInventory()
{
	Inventory->ToggleInventoryWidget();
}

void ACharacter_Base::OnFire()
{
	if(GetValueFor(EResourceType::AMMUNITION) <= 0)
	{
		if(GEngine && IsLocallyControlled()) GEngine->AddOnScreenDebugMessage(5, 5.f, FColor::Red, TEXT("Unable to shoot, there is no ammunition"));
		return;
	}
	SetNewValueForResource(EResourceType::AMMUNITION, GetValueFor(EResourceType::AMMUNITION) - 1);
}

void ACharacter_Base::Run(float val)
{
	if(val > 0.f && GetMovementComponent()->Velocity.Size() > 0.f && bIsRunning)
	{
		if(GetValueFor(EResourceType::STAMINA) <= 0)
		{
			StopRun();
			return;
		}
		SetNewValueForResource(EResourceType::STAMINA, GetValueFor(EResourceType::STAMINA) - (val * GetWorld()->DeltaTimeSeconds * 0.1f));
	}
}


void ACharacter_Base::StartRun()
{
	GetWorld()->GetTimerManager().ClearTimer(RunningDelayRechargeTimerHandle);
	bIsRunning = true;
}

void ACharacter_Base::StopRun()
{
	if(!bIsRunning) return;
	
	bIsRunning = false;
	
	FTimerDelegate RechargeDelegate;
	RechargeDelegate.BindLambda([=]()
	{
		if(!this || !IsValid(this)) return;
		
		SetNewValueForResource(EResourceType::STAMINA, GetValueFor(EResourceType::STAMINA) + StaminaConfig.RechargeAmount);
	});
	
	GetWorld()->GetTimerManager().SetTimer(RunningDelayRechargeTimerHandle, RechargeDelegate, StaminaConfig.RechargeInterval, true, 1.f);
}

int32 ACharacter_Base::GetValueFor(EResourceType Type)
{
	return CharacterResources->GetValueOf(Type);
}

void ACharacter_Base::SetNewStaminaConfig(FStaminaConfig NewStaminaConfig)
{
	this->StaminaConfig = NewStaminaConfig;
}

void ACharacter_Base::SetNewValueForResource_Implementation(EResourceType Type, int32 Value)
{
	CharacterResources->SetNewValueFor(Type, Value);
}

