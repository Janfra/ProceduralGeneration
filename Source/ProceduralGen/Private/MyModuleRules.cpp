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

TArray<TileTypes> UMyModuleRules::GetGroupConstraints(TArray<TileTypes> typeArr, Directions& direction)
{
	TArray<TileTypes> groupConstraints;

	// 'DirectionsConstraints' are set on the constructor to have same index order than the direction enum
	const int index = (int)direction;

	if (index < 0 || index >= (int)TileTypes::TYPES_COUNT) {
		UE_LOG(LogTemp, Warning, TEXT("Index (Direction) requested to the module rules is invalid %d"), index);
		return groupConstraints;
	}
	
	for (TileTypes& type : typeArr) 
	{
		if (typeNeighboursDictionary.Contains(type)) {
			groupConstraints.Append(typeNeighboursDictionary[type].DirectionConstraints[index].TilesPossible);
		}
		else 
		{
			UE_LOG(LogTemp, Warning, TEXT("Index (Type) requested to the module rules is invalid %d"), (int)type);
		}
	}

	return groupConstraints;
}