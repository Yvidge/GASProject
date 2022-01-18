// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "UI/UWAbilityBook.h"
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

	UPROPERTY(BlueprintReadOnly)
	UUWAbilityBook* AbilityBookWidget;

	UPROPERTY(EditDefaultsOnly, Category="UI")
	TSubclassOf<UUWMainHUD> HUDWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UUWAbilityBook> AbilityBookWidgetClass;

	virtual void BeginPlay() override;

public:

	UFUNCTION(BlueprintCallable)
	void OpenAbilityBook();

	UFUNCTION(BlueprintCallable)
	void CloseAbilityBook();

};
