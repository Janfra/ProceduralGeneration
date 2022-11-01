// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#define TOTAL_TYPES 3

#include "CoreMinimal.h"
#include "MyModuleRules.h"
#include "GameFramework/Actor.h"
#include "MyTestActor.generated.h"

UCLASS()
class PROCEDURALGEN_API AMyTestActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyTestActor();

	UPROPERTY(EditAnywhere, Category = "Visuals")
	UStaticMeshComponent* Mesh;
	UMyModuleRules* Rules;

	enum Directions 
	{
		Up,
		Left,
		Down,
		Right,
	};

	enum TileType
	{
		White,
		Green,
		Blue,
	};

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	void ChangeColour(FLinearColor newColour);

	void GetColour(Directions direction);

private:

	// UPROPERTY(VisibleAnywhere)
	// TArray<TileType> tileTypesPossible;
};
