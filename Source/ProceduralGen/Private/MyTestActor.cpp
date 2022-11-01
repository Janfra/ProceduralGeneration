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

	//for (int i = 0; i < TOTAL_TYPES; i++) 
	//{
	//	TileType type = static_cast<TileType>(i);
	//	tileTypesPossible.AddUnique(type);
	//}
}

// Called when the game starts or when spawned
void AMyTestActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void AMyTestActor::ChangeColour(FLinearColor newColour) 
{
	UMaterialInstanceDynamic* material = Mesh->CreateAndSetMaterialInstanceDynamic(0);
	if (material) {
		material->SetVectorParameterValue(TEXT("Color"), newColour);
	}
}

void AMyTestActor::GetColour(Directions direction) 
{

}