// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#define TOTAL_DIRECTIONS 4

#include "CoreMinimal.h"
#include "ModulePrototypes.h"
#include "TileTypesEnum.h"
#include "MyModuleRules.h"
#include "GameFramework/Actor.h"
#include "MyTestActor.generated.h"


UENUM()
enum class TileTypes : uint8
{
	White,
	Green,
	Blue,

	// This is used as my way of always knowing the total size of this enum. Keep at the end
	TYPES_COUNT
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
struct FTileTypeNeighbours {
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere)
	Directions Direction;

	UPROPERTY(VisibleAnywhere)
	TArray<TileTypes> TilesPossible;
	
	FTileTypeNeighbours() 
	{
		Direction = Directions::Down;
	}

	FTileTypeNeighbours(Directions direction, TArray<TileTypes> tileList) 
	{
		Direction = direction;
		TilesPossible.Append(tileList);
	}
};

UCLASS()
class PROCEDURALGEN_API AMyTestActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyTestActor();

	UPROPERTY(EditAnywhere, Category = "Visuals")
	UStaticMeshComponent* Mesh;

	UPROPERTY()
	UMyModuleRules* Rules;

	UPROPERTY(VisibleAnywhere, DisplayName = "Neighbour Constraints")
	FTileTypeNeighbours PossibleNeighbours[TOTAL_DIRECTIONS];

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	UFUNCTION()
	void ChangeColour(const FLinearColor& newColour);

	UFUNCTION()
	void SetType(const TileTypes& type);

	UFUNCTION()
	bool GetCollapsed();

	UFUNCTION()
	void SetTypes(TArray<TileTypes>& typeToBe);

	UFUNCTION()
	int8 GetTypeCount();

private:
	UPROPERTY(VisibleAnywhere)
		bool bCollapsed;

	UPROPERTY(VisibleAnywhere, DisplayName = "Types Available")
	TArray<TileTypes> possibleTypes;

private:
	UFUNCTION()
	FLinearColor GetColour(const TileTypes& type);

};
