// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "AGGameInstance.generated.h"

class UAGGameplayAbilityBase;
/**
 * 
 */
UCLASS()
class GASPROJECT_API UAGGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:

	TArray<TSubclassOf<UAGGameplayAbilityBase>> UnlockedAbilities;

};
