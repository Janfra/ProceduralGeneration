// Fill out your copyright notice in the Description page of Project Settings.


#include "GridGenerationActor.h"

// Sets default values
AGridGenerationActor::AGridGenerationActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Rules = CreateDefaultSubobject<UMyModuleRules>(TEXT("Rules"), false);

	// Create the transform and parenting of the grid
	Transform = CreateDefaultSubobject<USceneComponent>(TEXT("Transform"), false);

	height = 1;
	width = 1;
}

// Called when the game starts or when spawned
void AGridGenerationActor::BeginPlay()
{
	Super::BeginPlay();

	WaveFunctionCollapseGen();
}

// Called every frame
void AGridGenerationActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

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

#pragma endregion

 #pragma region Wave Function Collapse

void AGridGenerationActor::WaveFunctionCollapseGen() 
{
	GenerateGrid();

	// First iteration: Go through all slots in the grid, find the ones with lowest entropy and store them.
	TArray<AMyTestActor*> collapseOptions;
	int lowestEntropy = (int)TileTypes::TYPES_COUNT;
	AMyTestActor* selectedOption;

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
	
	// Propagate new constraints 
	Propagate(tileType, randomPick);
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

void AGridGenerationActor::Propagate(TileTypes& type, int& originIndex) 
{
	// Index for respectively: Up, Right, Down, Left.
	const int originFrontIndex = originIndex + 1;
	const int originRightIndex = originIndex + height;
	const int originBackIndex = originIndex - 1;
	const int originLeftIndex = originIndex - height;

	// Update slot based on direction
	for (int i = 0; i < TOTAL_DIRECTIONS; i++) 
	{
		switch (i)
		{
		case 0:
			UpdateSlot(ClampIndex(originFrontIndex), type, (Directions)i);
			break;
		case 1:
			UpdateSlot(ClampIndex(originRightIndex), type, (Directions)i);
			break;
		case 2:
			UpdateSlot(ClampIndex(originBackIndex), type, (Directions)i);
			break;
		case 3:
			UpdateSlot(ClampIndex(originLeftIndex), type, (Directions)i);
			break;

		default:
			break;
		}
	}
}

void AGridGenerationActor::UpdateSlot(const int& index, TileTypes& type, Directions direction)
{
	if (slotsUpdated.Contains(gridSlots[index])) {
		return;
	}
	gridSlots[index]->SetTypes(Rules->GetConstraints(type, direction));
	slotsUpdated.AddUnique(gridSlots[index]);
}

int AGridGenerationActor::ClampIndex(const int& index) 
{
	if (index <= 0) {
		return 0;
	}
	else if (index >= gridSlots.Num()) 
	{
		return gridSlots.Num() - 1;
	}
	return index;
}

#pragma endregion

