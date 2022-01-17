// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UWAbility.h"
#include "Blueprint/UserWidget.h"
#include "GAS/AGGameplayAbilityBase.h"
#include "UWAbilityPanel.generated.h"

/**
 * 
 */
UCLASS()
class GASPROJECT_API UUWAbilityPanel : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (BindWidget = "MainPanel"))
	class UHorizontalBox* MainPanel;

	//UPROPERTY(BlueprintReadWrite)
	TMap<UUWAbility*, UClass*> AbilitiesMap;


public:

	UFUNCTION(BlueprintCallable)
	void UpdateAbilityCooldown(const TSubclassOf<UAGGameplayAbilityBase> AbilityClass);

protected:

	virtual void NativeOnInitialized() override;

	UFUNCTION(BlueprintCallable)
	float GetAbilityCooldown(const TSubclassOf<UAGGameplayAbilityBase> AbilityClass);

	void InitializeAbilitiesMap();

};
