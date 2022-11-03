// Fill out your copyright notice in the Description page of Project Settings.


#include "MyModuleRules.h"

// Sets default values for this component's properties
UMyModuleRules::UMyModuleRules()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	//int8 directionIndex = 0;
	//for (FTileTypeNeighbours& currentDirection : PossibleNeighbours) {
	//	currentDirection.TilesPossible.Append(AllTypes);
	//	currentDirection.Direction = (Directions)directionIndex;
	//	directionIndex++;
	//}
}


// Called when the game starts
void UMyModuleRules::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

TArray<TileTypes> UMyModuleRules::GetConstraints(TileTypes& type, Directions& direction) 
{
	for (auto& directionConstraint : typeNeighboursDictionary[type].DirectionConstraints) 
	{
		if (directionConstraint.GetDirection() == direction) 
		{
			return directionConstraint.TilesPossible;
		}
	}

	// Should never get here
	TArray<TileTypes> empty;
	return empty;
}
