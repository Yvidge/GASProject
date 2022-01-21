// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/AGEnemyCharacter.h"
#include "GameFramework/Actor.h"
#include "EnemySpawner.generated.h"


USTRUCT(BlueprintType)
struct FEnemyTypeSpawnRules
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AAGEnemyCharacter> EnemyClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Num;

};

USTRUCT(BlueprintType)
struct FGroupSpawnRules
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (FullyExpand = true, ShowInnerProperties))
	TArray<FEnemyTypeSpawnRules> EnemyTypes;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SpawnDuration = 5.0f;

};

UCLASS(BlueprintType)
class GASPROJECT_API AEnemySpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemySpawner();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SpawnRules, meta=(FullyExpand = true, ShowInnerProperties))
	TArray<FGroupSpawnRules> SpawnRules;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SpawnRules)
	float SpawnRadius = 3000.0f;

	

protected:
	
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly)
	bool bSpawning = false;

	UPROPERTY(BlueprintReadOnly)
	int AliveEnemiesNum = 0;

	UPROPERTY(BlueprintReadOnly)
	int CurrentGroupIndex = 0;

	/*UPROPERTY(BlueprintReadOnly)
	TArray<AAGEnemyCharacter*> Enemies;*/

	UFUNCTION()
	void SpawnGroup();

	UFUNCTION()
	void EnemyDied(ACharacter* DiedCharacter);

public:	
	
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void StartSpawning();

	UFUNCTION(BlueprintImplementableEvent)
	void SpawningCompleted();

};
