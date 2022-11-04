// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#define TOTAL_DIRECTIONS 4

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MyModuleRules.generated.h"


UENUM()
enum class TileTypes : uint8
{
	White,
	Green,
	Blue,
	Red,
	Gray,

	// This is used as my way of always knowing the total size of this enum. Keep at the end
	TYPES_COUNT UMETA(Hidden)
};

UENUM()
enum class Directions : uint8
{
	Up,
	Right,
	Down,
	Left,
};

USTRUCT()
struct FTileDirectionNeighbours {
	GENERATED_BODY()

private:

	UPROPERTY(VisibleAnywhere)
	Directions Direction;

public:
	UPROPERTY(EditAnywhere)
	TArray<TileTypes> TilesPossible;

	Directions GetDirection() 
	{
		return Direction;
	}

	FTileDirectionNeighbours()
	{
		Direction = Directions::Up;
	}

	FTileDirectionNeighbours(Directions direction)
	{
		Direction = direction;
	}
};

USTRUCT()
struct FTileNeighboursArray 
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, EditFixedSize)
	TArray<FTileDirectionNeighbours> DirectionConstraints;

	FTileNeighboursArray()
	{
		for (int i = 0; i < TOTAL_DIRECTIONS; i++) 
		{
			DirectionConstraints.Add(FTileDirectionNeighbours((Directions)i));
		}
	}
};

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

private:
	UPROPERTY(EditAnywhere, DisplayName = "Neighbour Constraints")
	TMap<TileTypes, FTileNeighboursArray> typeNeighboursDictionary;

public:	
	TArray<TileTypes> GetConstraints(TileTypes& type, Directions& direction);

	TArray<TileTypes> GetGroupConstraints(TArray<TileTypes> typeArr, Directions& direction);
};
