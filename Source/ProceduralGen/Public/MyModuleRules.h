// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MyModuleRules.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROCEDURALGEN_API UMyModuleRules : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMyModuleRules();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	bool collapse;

	enum Options 
	{
		Blank,
		Up,
		Right,
		Down,
		Left,

	};

public:	

};
