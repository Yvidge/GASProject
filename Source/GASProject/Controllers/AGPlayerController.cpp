// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/AGPlayerController.h"
#include  "UI/UWMainHUD.h"

void AAGPlayerController::BeginPlay()
{
	Super::BeginPlay();

	HUDWidget = CreateWidget<UUWMainHUD>(this, HUDWidgetClass);
	HUDWidget->AddToViewport();

}
