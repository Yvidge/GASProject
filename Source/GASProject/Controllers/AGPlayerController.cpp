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
	}
}
