// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/UWAbilityPanel.h"

#include "Components/HorizontalBox.h"
#include "Controllers/AGPlayerController.h"
#include "Kismet/GameplayStatics.h"

void UUWAbilityPanel::UpdateAbilityCooldown(const TEnumAsByte<EGDAbilityInputID> Binding,
	const TSubclassOf<UAGGameplayAbilityBase> Class)
{
	for (TTuple<UUWAbility*, TEnumAsByte<EGDAbilityInputID>> Pair : AbilitiesMap)
	{
		if(Pair.Value == Binding)
		{
			Pair.Key->StartUpdatingCooldown(Class.GetDefaultObject()->CooldownDuration.GetValue());
		}
	}

}

void UUWAbilityPanel::UpdateAbilitySlotBinding(const TEnumAsByte<EGDAbilityInputID> Binding,
	const TSubclassOf<UAGGameplayAbilityBase> Class)
{
	for (TTuple<UUWAbility*, TEnumAsByte<EGDAbilityInputID>> Pair : AbilitiesMap)
	{
		if(Pair.Value == Binding)
		{
			Pair.Key->AbilityClass = Class;
			Pair.Key->InitializeFromAbilityClass(Class);
		}
	}
}

void UUWAbilityPanel::NativeOnInitialized()
{
	InitializeAbilitiesMap();

	AAGPlayerController* PlayerController = Cast<AAGPlayerController>(UGameplayStatics::GetPlayerController(this, 0));
	if(PlayerController)
	{
		PlayerController->OnAbilityBindingChanged.AddDynamic(this, &UUWAbilityPanel::UpdateAbilitySlotBinding);
		PlayerController->OnAbilityBindingUsed.AddDynamic(this, &UUWAbilityPanel::UpdateAbilityCooldown);
	}

}

void UUWAbilityPanel::InitializeAbilitiesMap()
{
	//MainPanel->GetAllChildren()
	for (UWidget* Widget : MainPanel->GetAllChildren())
	{
		UUWAbility* AbilityWidget = Cast<UUWAbility>(Widget);
		if(AbilityWidget)
		{
			AbilitiesMap.Add(AbilityWidget, AbilityWidget->AbilityBind);
		}
	}
}
