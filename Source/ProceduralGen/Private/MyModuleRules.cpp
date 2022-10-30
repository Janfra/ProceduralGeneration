// Fill out your copyright notice in the Description page of Project Settings.


#include "MyModuleRules.h"

// Sets default values for this component's properties
UMyModuleRules::UMyModuleRules()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
	collapse = false;
}


// Called when the game starts
void UMyModuleRules::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


