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

	TArray<TileTypes> AllTypes;
	for (int i = 0; i < (int)TileTypes::TYPES_COUNT; i++) {
		AllTypes.AddUnique((TileTypes)i);
	}

	possibleTypes.Append(AllTypes);

	bCollapsed = false;
}

// Called when the game starts or when spawned
void AMyTestActor::BeginPlay()
{
	Super::BeginPlay();
	
}

/// <summary>
/// Changes the colour of the mesh of this actor
/// </summary>
/// <param name="newColour">Colour to set</param>
void AMyTestActor::ChangeColour(const FLinearColor& newColour) 
{
	UMaterialInstanceDynamic* material = Mesh->CreateAndSetMaterialInstanceDynamic(0);
	if (material) {
		material->SetVectorParameterValue(TEXT("Color"), newColour);
	}
}

/// <summary>
/// Returns a colour based on the type given
/// </summary>
/// <param name="type">Type to check</param>
/// <returns>Returns colour associated to the given type</returns>
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
	case TileTypes::Red:
		return FLinearColor::Red;
	case TileTypes::Gray:
		return FLinearColor::Gray;
	}

	return FLinearColor::Black;
}

/// <summary>
/// Sets the type of this actor
/// </summary>
/// <param name="type">Type to set</param>
void AMyTestActor::SetType(const TileTypes& type) 
{
	possibleTypes.Empty();
	ChangeColour(GetColour(type));
	possibleTypes.AddUnique(type);
	bCollapsed = true;
}

/// <summary>
/// Returns the collapsed state of this actor
/// </summary>
/// <returns>Returns if this actor has collapsed</returns>
bool AMyTestActor::GetCollapsed() 
{
	return bCollapsed;
}

/// <summary>
/// Updates the possible types of this actor using the given array
/// </summary>
/// <param name="typeToBe">Array to compare it with</param>
/// <returns>Returns true if the possibilities were changed</returns>
bool AMyTestActor::SetTypes(TArray<TileTypes> typeToBe) 
{
	TArray<TileTypes> newTypesAvailable;

	// If already possible, keep it as possible, otherwise remove it.
	for (auto& currentTileConstraint : typeToBe) 
	{
		if (possibleTypes.Contains(currentTileConstraint)) 
		{
			newTypesAvailable.AddUnique(currentTileConstraint);
		}
	}

	// No changes made
	if (newTypesAvailable.Num() == possibleTypes.Num()) 
	{
		return false;
	}
	
	// Check in case the possible types is now going to be empty
	if (newTypesAvailable.IsEmpty())
	{
		UObject* test = this;
		FString objectName = test->GetName();

		UE_LOG(LogTemp, Warning, TEXT("The types set in %s was empty! - SetTypes"), *objectName);
	}

	possibleTypes.Empty();
	possibleTypes.Append(newTypesAvailable);

	return true;
}

/// <summary>
/// Gets the number of types possible
/// </summary>
/// <returns>How many possible types can this actor be</returns>
int8 AMyTestActor::GetTypeCount() 
{
	return possibleTypes.Num();
}

/// <summary>
/// Get a random type out of the possible types
/// </summary>
/// <returns>One of the possible types</returns>
TileTypes AMyTestActor::GetType() 
{
	// Possible types empty warning
	if (possibleTypes.IsEmpty()) 
	{
		UObject* test = this;
		FString objectName = test->GetName();

		UE_LOG(LogTemp, Warning, TEXT("Actor possible types is empty! - GetType in %s"), *objectName);
		return TileTypes::White;
	}

	if (possibleTypes.Num() > 1) {
		return possibleTypes[FMath::RandRange(0, possibleTypes.Num() - 1)];
	} 
	else
	{
		return possibleTypes[0];
	}
}

/// <summary>
/// Gets the array of possible types
/// </summary>
/// <returns>Possible types array</returns>
TArray<TileTypes> AMyTestActor::GetPossibleTypes() 
{
	if(!possibleTypes.IsEmpty())
	{
		return possibleTypes;
	}
	
	// Possible types empty warning
	UObject* test = this;
	FString objectName = test->GetName();

	UE_LOG(LogTemp, Warning, TEXT("Actor possible types is empty! - GetPossibleTypes in %s and their collapsed state is %s"), *objectName, (bCollapsed ? TEXT("true") : TEXT("false")));
	possibleTypes.AddUnique(TileTypes::White);
	return possibleTypes;
}