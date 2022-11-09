// Fill out your copyright notice in the Description page of Project Settings.


#include "GridGenerationActor.h"

// Sets default values
AGridGenerationActor::AGridGenerationActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Rules = CreateDefaultSubobject<UMyModuleRules>(TEXT("Rules"), false);

	// Create the transform and parenting of the grid
	Transform = CreateDefaultSubobject<USceneComponent>(TEXT("Transform"), false);

	height = 1;
	width = 1;

	collapsedCount = 0;
}

// Called when the game starts or when spawned
void AGridGenerationActor::BeginPlay()
{
	Super::BeginPlay();

	WaveFunctionCollapseGen();
}

 #pragma region TestGeneration

/// <summary>
/// Based on this actor location, generate the grid.
/// </summary>
void AGridGenerationActor::GenerateGrid() 
{
	FVector gridStartPos;
	GetGridStartPos(gridStartPos);

	for (int y = 0; y / TILE_SIZE < height; y += TILE_SIZE) 
	{
		for (int x = 0; x / TILE_SIZE < width; x += TILE_SIZE) 
		{
			FVector currentLocation;
			currentLocation.Set(x + gridStartPos.X, y + gridStartPos.Y, 0);

			AMyTestActor* test = GetWorld()->SpawnActor<AMyTestActor>(testClass, currentLocation, GetActorRotation());
			test->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);
			test->SetRootComponent(Transform);
			test->ChangeColour(FLinearColor::Red);
			gridSlots.AddUnique(test);
		}
	}
}

/// <summary>
/// Turns the given vector to be at the starting position of the grid based on actor position
/// </summary>
/// <param name="vector"></param>
void AGridGenerationActor::GetGridStartPos(FVector& vector)
{
	vector = GetActorLocation();
	CentreGrid(vector);
}

/// <summary>
/// Move the grid starting location to centre the actor
/// </summary>
/// <param name="vectorToAlign">Vector to modify</param>
void AGridGenerationActor::CentreGrid(FVector& vectorToAlign)
{
	vectorToAlign.X -= ((width * TILE_SIZE) / 2) - TILE_SIZE / 2;
	vectorToAlign.Y -= ((height * TILE_SIZE) / 2) - TILE_SIZE / 2;
}

#pragma endregion

 #pragma region Wave Function Collapse

/// <summary>
/// WFC generation function, generates randomly based on the given rules. 
/// </summary>
void AGridGenerationActor::WaveFunctionCollapseGen() 
{
	collapsedCount = 0;
	GenerateGrid();

	// Per iteration: Go through all slots in the grid, find the ones with lowest entropy and store them.
	TArray<AMyTestActor*> collapseOptions;
	int lowestEntropy = (int)TileTypes::TYPES_COUNT;
	AMyTestActor* selectedOption;
	
	while (!HasCollapsed()) {
		for (auto& slot : gridSlots) 
		{
			if (!slot->GetCollapsed()) 
			{
				int currentEntropy = slot->GetTypeCount();
				if (currentEntropy < lowestEntropy) 
				{
					lowestEntropy = currentEntropy;
					collapseOptions.Empty();
					collapseOptions.AddUnique(slot);
				} 
				else if (currentEntropy == lowestEntropy) 
				{
					collapseOptions.AddUnique(slot);
				}
			}
		}

		// With the new list, pick one randomly and collapse it with a random type.
		int randomPick = FMath::RandRange(0, collapseOptions.Num() - 1);
		selectedOption = collapseOptions[randomPick];
		TileTypes tileType = selectedOption->GetType();
		selectedOption->SetType(tileType);
		//collapsedCount++; - 9 away from total every time
	
		// Propagate new constraints 
		Propagate(tileType, randomPick);
	}
}

/// <summary>
/// Updates all tiles affected by the new constraints
/// </summary>
/// <param name="type">Origin tile type to start propagation</param>
/// <param name="originIndex">Origin tile index</param>
void AGridGenerationActor::Propagate(TileTypes& type, int& originIndex) 
{
	// Index
	TQueue<int> indexToPropagateTo;
	indexToPropagateTo.Enqueue(originIndex);

	// TileType constraints
	TQueue<TArray<TileTypes>> typesToPropagate;
	TArray<TileTypes> initializeArr;
	initializeArr.Add(type);
	typesToPropagate.Enqueue(initializeArr);

	while (!indexToPropagateTo.IsEmpty()) 
	{
		int currentIndex;
		indexToPropagateTo.Dequeue(currentIndex);
		TArray<TileTypes> currentTypeArr;
		typesToPropagate.Dequeue(currentTypeArr);

		// If a tile is updated, add it to the queue to check if neighbours also need to be updated
		for (auto& index : PropagateAround(currentTypeArr, currentIndex)) 
		{
			typesToPropagate.Enqueue(gridSlots[index]->GetPossibleTypes());
			indexToPropagateTo.Enqueue(index);
		}
		UE_LOG(LogTemp, Warning, TEXT("Propagated to %d"), currentIndex);
	}
}

/// <summary>
/// Updates tiles adjacent to the given tile.
/// </summary>
/// <param name="typeArr">List of tiles available in origin tile</param>
/// <param name="originIndex">Origin tile index</param>
/// <returns>Index of the tiles that were updated</returns>
TArray<int> AGridGenerationActor::PropagateAround(TArray<TileTypes>& typeArr, int& originIndex) 
{
	TArray<int> indexesToCheck;

	// Index for respectively: Up, Right, Down, Left.
	const int originFrontIndex = originIndex + 1;
	const int originRightIndex = originIndex + height;
	const int originBackIndex = originIndex - 1;
	const int originLeftIndex = originIndex - height;

	// Index value to be clamped, also to check that origin is not included in the queue.
	int clampedIndex;

	for (int i = 0; i < TOTAL_DIRECTIONS; i++)
	{
		// Set the index to be clamped depending on direction
		switch (i)
		{
		case 0:
			clampedIndex = originFrontIndex;
			break;
		case 1:
			clampedIndex = originRightIndex;
			break;
		case 2:
			clampedIndex = originBackIndex;
			break;
		case 3:
			clampedIndex = originLeftIndex;
			break;
		default:
			break;
		}

		// Try to update slot with current index, if true add it to the list to check its neighbours
		if (UpdateSlot(clampedIndex, typeArr, (Directions)i))
		{
			if (clampedIndex != originIndex)
				indexesToCheck.AddUnique(clampedIndex);
		}
	}

	return indexesToCheck;
}

/// <summary>
/// Update the slot to their new constraints 
/// </summary>
/// <param name="index">Index of the slot</param>
/// <param name="type">Type collapsed</param>
/// <param name="direction">Direction of the update</param>
/// <returns>Was the slot updated</returns>
bool AGridGenerationActor::UpdateSlot(int& index, TArray<TileTypes> typeArr, Directions direction)
{
	ClampIndex(index);
	return gridSlots[index]->SetTypes(Rules->GetGroupConstraints(typeArr, direction));
}

/// <summary>
/// Clamp the given index to the grid size 
/// </summary>
/// <param name="index">Index being clamped</param>
void AGridGenerationActor::ClampIndex(int& index) 
{
	if (index <= 0) {
		index = 0;
		return;
	}
	else if (index >= gridSlots.Num()) 
	{
		index =	gridSlots.Num() - 1;
	}
}

/// <summary>
/// Returns if the WFC has fully collapsed/observed
/// </summary>
/// <returns>Returns true if WFC has fully collapsed</returns>
bool AGridGenerationActor::HasCollapsed() 
{
	for (auto& slots : gridSlots) 
	{
		if (slots->GetCollapsed()) 
		{
			collapsedCount++;
		}
	}

	if (collapsedCount == gridSlots.Num()) 
	{
		return true;
	}
	return false;
}

#pragma endregion

#pragma region Outdated

/*for (auto& type : gridSlots[index]->GetPossibleTypes())
{
	indexToPropagateTo.Enqueue(index);
	typesToPropagate.Enqueue(type);
}*/

#pragma endregion
