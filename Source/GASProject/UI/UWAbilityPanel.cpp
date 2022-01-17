// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/UWAbilityPanel.h"

#include "Components/HorizontalBox.h"

void UUWAbilityPanel::UpdateAbilityCooldown(const TSubclassOf<UAGGameplayAbilityBase> AbilityClass)
{
	for (TTuple<UUWAbility*, UClass*> Pair : AbilitiesMap)
	{
		if(Pair.Value == AbilityClass)
		{
			Pair.Key->StartUpdatingCooldown(AbilityClass.GetDefaultObject()->CooldownDuration.GetValue());
		}
	}

}

void UUWAbilityPanel::NativeOnInitialized()
{
	InitializeAbilitiesMap();
}

float UUWAbilityPanel::GetAbilityCooldown(const TSubclassOf<UAGGameplayAbilityBase> AbilityClass)
{
	//AbilitiesMap.FindKey(AbilityClass);
	return 0;
}

void UUWAbilityPanel::InitializeAbilitiesMap()
{
	//MainPanel->GetAllChildren()
	for (UWidget* Widget : MainPanel->GetAllChildren())
	{
		UUWAbility* AbilityWidget = Cast<UUWAbility>(Widget);
		if(AbilityWidget)
		{
			AbilitiesMap.Add(AbilityWidget, AbilityWidget->AbilityClass);
		}
	}
}
