// Fill out your copyright notice in the Description page of Project Settings.


#include "GenSlot.h"

// Sets default values for this component's properties
UGenSlot::UGenSlot()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
	Collapse = false;
}


// Called when the game starts
void UGenSlot::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

