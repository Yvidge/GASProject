// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/UWAbilityBookSlot.h"
#include "UI/UWAbilityBookRow.h"

void UUWAbilityBookSlot::NativeOnInitialized()
{
	SelectButton->OnClicked.AddDynamic(this, &UUWAbilityBookSlot::HandleSlotSelection);
}

void UUWAbilityBookSlot::HandleSlotSelection()
{
	if(OwnerRow)
	{
		OwnerRow->SetAbility(AbilityClass);
	}
}
