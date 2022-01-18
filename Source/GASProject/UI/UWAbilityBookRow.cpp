// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/UWAbilityBookRow.h"

#include "UWAbilityBookSlot.h"

void UUWAbilityBookRow::GeneratePossibleAbilities()
{
}

void UUWAbilityBookRow::InitializeChildrenSlots()
{
	for (UWidget* Widget : PossibleAbilitiesPanel->GetAllChildren())
	{
		UUWAbilityBookSlot* AbilitySlot = Cast<UUWAbilityBookSlot>(Widget);
		if(AbilitySlot)
		{
			AbilitySlot->OwnerRow = this;
		}
	}
}

void UUWAbilityBookRow::SetAbility(const TSubclassOf<UAGGameplayAbilityBase> AbilityClass)
{
	if(AbilityClass)
	{
		SelectedAbilityIcon->SetBrushFromTexture(AbilityClass.GetDefaultObject()->AbilityIcon);
	}
}

void UUWAbilityBookRow::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	InitializeChildrenSlots();
}
