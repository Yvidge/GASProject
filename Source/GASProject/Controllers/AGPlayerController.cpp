// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/AGPlayerController.h"
#include  "UI/UWMainHUD.h"

void AAGPlayerController::BeginPlay()
{
	Super::BeginPlay();

	HUDWidget = CreateWidget<UUWMainHUD>(this, HUDWidgetClass);
	HUDWidget->AddToViewport();

}

void AAGPlayerController::OpenAbilityBook()
{
	if(AbilityBookWidget)
	{
		AbilityBookWidget->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		AbilityBookWidget = CreateWidget<UUWAbilityBook>(this, AbilityBookWidgetClass);
		AbilityBookWidget->AddToViewport(2);
	}

}

void AAGPlayerController::CloseAbilityBook()
{
	if(AbilityBookWidget)
	{
		AbilityBookWidget->SetVisibility(ESlateVisibility::Collapsed);
		AbilityBookWidget->Destruct();
		AbilityBookWidget = nullptr;
	}
}

void AAGPlayerController::UpdateAbilityBinding(const TEnumAsByte<EGDAbilityInputID> InputBind,
	const TSubclassOf<UAGGameplayAbilityBase> AbilityBind)
{
	if(AbilityBind)
	{
		TArray<EGDAbilityInputID> Keys;
		AbilityInputBindings.GetKeys(Keys);
		AbilityInputBindings.Add(Keys[Keys.Find(InputBind)], AbilityBind);
		OnAbilityBindingChanged.Broadcast(InputBind, AbilityBind);

	}
}

void AAGPlayerController::UseAbilityByInputBinding(const TEnumAsByte<EGDAbilityInputID> InputBind)
{

	for (TTuple<EGDAbilityInputID, TSubclassOf<UAGGameplayAbilityBase>> Binding : AbilityInputBindings)
	{
		if(Binding.Key == InputBind)
		{
			auto PlayerCharacter = Cast<AGASProjectCharacter>(GetPawn());
			if(PlayerCharacter->GetAbilitySystemComponent()->TryActivateAbilityByClass(Binding.Value))
			{
				OnAbilityBindingUsed.Broadcast(Binding.Key, Binding.Value);
			}
			
		}
	}

}

TSubclassOf<UAGGameplayAbilityBase> AAGPlayerController::GetAbilityByBinding(const TEnumAsByte<EGDAbilityInputID> InputBind)
{
	return *AbilityInputBindings.Find(InputBind);
}
