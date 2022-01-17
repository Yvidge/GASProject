// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/UWAbility.h"

void UUWAbility::InitializeFromAbilityClass(const TSubclassOf<UAGGameplayAbilityBase> Class)
{
	AbilityIcon->SetBrushFromTexture(AbilityClass.GetDefaultObject()->AbilityIcon);
}
