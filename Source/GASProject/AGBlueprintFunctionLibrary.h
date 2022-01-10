// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GASProjectCharacter.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "AGBlueprintFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class GASPROJECT_API UAGBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	UFUNCTION(BlueprintCallable, Category=AbilitySystemAI)
	static AGASProjectCharacter* FindTargetForHealing(const AActor* Instigator, const FVector& Origin, float Range);

};
