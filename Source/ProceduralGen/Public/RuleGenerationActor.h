// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyModuleRules.h"
#include "GameFramework/Actor.h"
#include "RuleGenerationActor.generated.h"

UCLASS()
class PROCEDURALGEN_API ARuleGenerationActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARuleGenerationActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/// 1. Going to need to manually assign every face with a socket or make it analyze a grid created by hand.

	/// 2. Once all sockets have be assigned / the grid is created to analyze, it will loop through all of them to match which ones can be neighbours

	/// 3. Then create a dictionary using the tile type as key and create a struct of FTileNeighboursArray for each direction

	/// 4. Create a JSON with the dictionary created

	/// 5. Load the new JSON to the MyModuleRules component

};
