// Fill out your copyright notice in the Description page of Project Settings.


#include "GridGenerationActor.h"

// Sets default values
AGridGenerationActor::AGridGenerationActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create the transform and parenting of the grid
	Transform = CreateDefaultSubobject<USceneComponent>(TEXT("Transform"), false);

	height = 1;
	width = 1;
}

// Called when the game starts or when spawned
void AGridGenerationActor::BeginPlay()
{
	Super::BeginPlay();

	GenerateGrid();
}

// Called every frame
void AGridGenerationActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

/// <summary>
/// Based on this actor location, generate the grid.
/// </summary>
void AGridGenerationActor::GenerateGrid() 
{
	FVector gridLocation = GetActorLocation();
	//GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Green, FString::Printf(TEXT("Current location of grid: %s"), *GetActorLocation().ToString()));

	CentreGrid(gridLocation);

	for (int y = 0; y / TILE_SIZE < height; y += TILE_SIZE) 
	{
		for (int x = 0; x / TILE_SIZE < width; x += TILE_SIZE) 
		{
			FVector currentLocation;
			currentLocation.Set(x + gridLocation.X, y + gridLocation.Y, 0);

			AMyTestActor* test = GetWorld()->SpawnActor<AMyTestActor>(testClass, currentLocation, GetActorRotation());
			test->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);
			test->SetRootComponent(Transform);
			gridModules.AddUnique(test);
		}
	}
}

/// <summary>
/// Move the grid starting location to centre the actor
/// </summary>
/// <param name="vectorToAlign">Vector to modify</param>
void AGridGenerationActor::CentreGrid(FVector &vectorToAlign) 
{
	vectorToAlign.X -= ((width * TILE_SIZE) / 2) - TILE_SIZE / 2;
	vectorToAlign.Y -= ((height * TILE_SIZE) / 2) - TILE_SIZE / 2;
}
