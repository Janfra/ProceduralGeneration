// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#define TILE_SIZE 100

#include "CoreMinimal.h"
#include "MyTestActor.h"
#include "GameFramework/Actor.h"
#include "GridGenerationActor.generated.h"


UCLASS()
class PROCEDURALGEN_API AGridGenerationActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGridGenerationActor();

	UPROPERTY(EditAnywhere, Category = "Generation", DisplayName = "Grid Height")
		int8 height;
	UPROPERTY(EditAnywhere, Category = "Generation", DisplayName = "Grid Width")
		int8 width;
	UPROPERTY(VisibleAnywhere, Category = "Transform")
		USceneComponent* Transform;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(VisibleAnywhere, Category = "Generation", DisplayName = "Grid")
		TArray<FVector> gridSlots;

	UPROPERTY(EditAnywhere, Category = "Generation", DisplayName = "Test to Generate")
		TSubclassOf<AMyTestActor> testClass = AMyTestActor::StaticClass();
	
	void ExampleGenerateGrid();

	void GenerateGrid();

	void WaveFunctionCollapseGen();

	void GetGridStartPos(FVector &vector);

	void CentreGrid(FVector &vectorToAlign);

};