// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "GAS/AGGameplayAbilityBase.h"
#include "UWAbility.generated.h"

/**
 * 
 */
UCLASS()
class GASPROJECT_API UUWAbility : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (BindWidget = "AbilityIcon"))
	UImage* AbilityIcon;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (BindWidget = "CooldownBar"))
	UProgressBar* CooldownBar;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (BindWidget = "CooldownLabel"))
	UTextBlock* CooldownLabel;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (BindWidget = "InputLabel"))
	UTextBlock* InputLabel;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(ExposeOnSpawn=true))
	TSubclassOf<UAGGameplayAbilityBase> AbilityClass;

	UFUNCTION(BlueprintCallable)
	void InitializeFromAbilityClass(const TSubclassOf<UAGGameplayAbilityBase> Class);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void StartUpdatingCooldown(float Cooldown);

};
