// Fill out your copyright notice in the Description page of Project Settings.


#include "Interactive_Base.h"

#include "Kismet/GameplayStatics.h"

// Sets default values
AInteractive_Base::AInteractive_Base()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AInteractive_Base::BeginPlay()
{
	Super::BeginPlay();
	if(!GetOwner())
	{
		SetOwner(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	}
}