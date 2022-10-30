// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyModuleRules.h"
#include "Components/ActorComponent.h"
#include "GenSlot.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROCEDURALGEN_API UGenSlot : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGenSlot();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	UPROPERTY(VisibleAnywhere)
		bool Collapse;
	TArray<UMyModuleRules::Options> OptionsAvailable;
};
