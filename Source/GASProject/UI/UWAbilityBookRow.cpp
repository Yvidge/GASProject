// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/UWAbilityBookRow.h"

#include "UWAbilityBookSlot.h"
#include "Controllers/AGPlayerController.h"
#include "Kismet/GameplayStatics.h"

void UUWAbilityBookRow::GeneratePossibleAbilities()
{
	AGASProjectCharacter* PlayerCharacter = Cast<AGASProjectCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
	for (FGameplayAbilitySpec ActivatableAbility : PlayerCharacter->GetAbilitySystemComponent()->GetActivatableAbilities())
	{
		//GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Blue, ActivatableAbility.GetDebugString());
		UUWAbilityBookSlot* CreatedSlot = CreateWidget<UUWAbilityBookSlot>(this, AbilitySlotClass);
		CreatedSlot->AbilityClass = ActivatableAbility.Ability->GetClass();
		PossibleAbilitiesPanel->AddChild(CreatedSlot);
	}
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
		AAGPlayerController* PlayerController = Cast<AAGPlayerController>(UGameplayStatics::GetPlayerController(this, 0));
		if(PlayerController)
		{
			PlayerController->UpdateAbilityBinding(InputBind, AbilityClass);
		}
	}
}

void UUWAbilityBookRow::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	GeneratePossibleAbilities();
	InitializeChildrenSlots();
}
