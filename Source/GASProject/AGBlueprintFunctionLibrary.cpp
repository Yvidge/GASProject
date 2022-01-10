// Fill out your copyright notice in the Description page of Project Settings.


#include "AGBlueprintFunctionLibrary.h"

#include "Characters/AGEnemyCharacter.h"
#include "Kismet/KismetSystemLibrary.h"

AGASProjectCharacter* UAGBlueprintFunctionLibrary::FindTargetForHealing(const AActor* Instigator, const FVector& Origin, float Range)
{
	TArray<AActor*> ActorsToIgnore;
	TArray<AActor*> PossibleTargets;
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes = { ObjectTypeQuery3 };
	//EObjectTypeQuery ObjType = EObjectTypeQuery::
	UKismetSystemLibrary::SphereOverlapActors(Instigator, Origin, Range, ObjectTypes, AGASProjectCharacter::StaticClass(), ActorsToIgnore, PossibleTargets);
	TMap<AAGEnemyCharacter*, int> PointsMap;
	for (AActor* PossibleTarget : PossibleTargets)
	{
		AAGEnemyCharacter* FriendlyTarget = Cast<AAGEnemyCharacter>(PossibleTarget);
		if(FriendlyTarget)
		{
			float RoleModifier = 0;
			switch (FriendlyTarget->CharacterRole)
			{
			case None: 
				RoleModifier = 1;
				break;
			case Player: 
				RoleModifier = 0;
				break;
			case Frontline: 
				RoleModifier = 2;
				break;
			case Backline: 
				RoleModifier = 1;
				break;
			case Support:
				RoleModifier = 0.4;
				break;
			}
			int CalculatedPoints = 100 * RoleModifier * (1 - FriendlyTarget->GetHealth()/FriendlyTarget->GetMaxHealth());
			PointsMap.Add(FriendlyTarget, CalculatedPoints);
			GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Orange, FString::Printf(TEXT("%s: %i"), ToCStr(FriendlyTarget->GetHumanReadableName()), CalculatedPoints));
		}
	}
	PointsMap.ValueSort([](int A, int B) { return A > B; });
	TArray<AAGEnemyCharacter*> Targets;
	PointsMap.GenerateKeyArray(Targets);
	return Targets[0];
}
