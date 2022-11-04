// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "ModulePrototypes.h"
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
	bool SetTypes(TArray<TileTypes> typeToBe);

	UFUNCTION()
	int8 GetTypeCount();

	UFUNCTION()
	TileTypes GetType();

	UFUNCTION()
	TArray<TileTypes> GetPossibleTypes();

private:
	UPROPERTY(VisibleAnywhere)
	bool bCollapsed;

	UPROPERTY(VisibleAnywhere, DisplayName = "Types Available")
	TArray<TileTypes> possibleTypes;

private:
	UFUNCTION()
	FLinearColor GetColour(const TileTypes& type);

};
