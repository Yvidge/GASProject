// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "AGPlayerController.generated.h"

class UUWMainHUD;
/**
 * 
 */
UCLASS()
class GASPROJECT_API AAGPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadOnly)
	UUWMainHUD* HUDWidget;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUWMainHUD> HUDWidgetClass;

	virtual void BeginPlay() override;

};
