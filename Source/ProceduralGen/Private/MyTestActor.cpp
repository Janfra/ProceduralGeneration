 // Fill out your copyright notice in the Description page of Project Settings.


#include "MyTestActor.h"

// Sets default values
AMyTestActor::AMyTestActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"), false);
	
	// Getting the cube mesh, storing the reference object and then setting the mesh.
	const ConstructorHelpers::FObjectFinder<UStaticMesh>MeshAsset(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube'"));
	UStaticMesh* newStaticMesh = MeshAsset.Object;
	Mesh->SetStaticMesh(newStaticMesh);

	Rules = CreateDefaultSubobject<UMyModuleRules>(TEXT("Rules"), false);

	TArray<TileTypes> AllTypes;
	for (int i = 0; i < (int)TileTypes::TYPES_COUNT; i++) {
		AllTypes.AddUnique((TileTypes)i);
	}

	int8 directionIndex = 0;
	for (FTileTypeNeighbours& currentDirection : PossibleNeighbours) {
		currentDirection.TilesPossible.Append(AllTypes);
		currentDirection.Direction = (Directions)directionIndex;
		directionIndex++;
	}

	bCollapsed = false;
}

// Called when the game starts or when spawned
void AMyTestActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void AMyTestActor::ChangeColour(const FLinearColor& newColour) 
{
	UMaterialInstanceDynamic* material = Mesh->CreateAndSetMaterialInstanceDynamic(0);
	if (material) {
		material->SetVectorParameterValue(TEXT("Color"), newColour);
	}
}

FLinearColor AMyTestActor::GetColour(const TileTypes& type) 
{
	switch (type) 
	{
	case TileTypes::Blue:
		return FLinearColor::Blue;
	case TileTypes::Green:
		return FLinearColor::Green;
	case TileTypes::White:
		return FLinearColor::White;
	}

	return FLinearColor::Gray;
}

void AMyTestActor::SetType(const TileTypes& type) 
{
	ChangeColour(GetColour(type));
	bCollapsed = true;
}

bool AMyTestActor::GetCollapsed() 
{
	return bCollapsed;
}

void AMyTestActor::SetTypes(TArray<TileTypes>& typeToBe) 
{
	TArray<TileTypes> newTypesAvailable;
	for (TileTypes& currentTileConstraint : typeToBe) 
	{
		if (possibleTypes.Contains(currentTileConstraint)) 
		{
			newTypesAvailable.AddUnique(currentTileConstraint);
		}
	}
	possibleTypes.Empty();
	possibleTypes.Append(newTypesAvailable);
}

int8 AMyTestActor::GetTypeCount() 
{
	return possibleTypes.Num();
}