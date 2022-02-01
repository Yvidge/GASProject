// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemySpawner.h"
#include "NavigationSystem.h"

// Sets default values
AEnemySpawner::AEnemySpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEnemySpawner::BeginPlay()
{
	Super::BeginPlay();
	
}

void AEnemySpawner::SpawnGroup()
{
	if(SpawnRules.IsValidIndex(CurrentGroupIndex))
	{
		for (FEnemyTypeSpawnRules EnemyType : SpawnRules[CurrentGroupIndex].EnemyTypes)
		{
			for (int i = 0; i < EnemyType.Num; ++i)
			{
				FRotator Rot(0);
				FVector Loc;
				FNavLocation ResultLoc;
				UNavigationSystemV1* NavSys = UNavigationSystemV1::GetCurrent(GetWorld());
				//NavSys->GetRandomReachablePointInRadius(GetActorLocation(), SpawnRadius, ResultLoc);
				//Loc[0] = FMath::RandRange(GetActorLocation())
				Loc = FMath::VRand();
				Loc[2] = 0;
				Loc *= SpawnRadius;
				Loc += GetActorLocation();
				FActorSpawnParameters Parameters;
				Parameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
				Loc[2] += HeightOffset;
				auto SpawnedEnemy = GetWorld()->SpawnActor<AAGEnemyCharacter>(EnemyType.EnemyClass, Loc, Rot, Parameters);
				SpawnedEnemy->OnDiedDelegate.AddDynamic(this, &AEnemySpawner::EnemyDied);
				AliveEnemiesNum++;
			}
		}
		CurrentGroupIndex++;
	}
	else
	{
		bSpawning = false;
		CurrentGroupIndex = 0;
		SpawningCompleted();
		OnSpawnPointCompleted.Broadcast();
	}
}

void AEnemySpawner::EnemyDied(ACharacter* DiedCharacter)
{
	AliveEnemiesNum--;

	if(AliveEnemiesNum == 0)
	{
		SpawnGroup();
		GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, TEXT("New group of enemies is spawned"));
	}

}

// Called every frame
void AEnemySpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEnemySpawner::StartSpawning()
{
	bSpawning = true;
	CurrentGroupIndex = 0;
	SpawnGroup();

}

