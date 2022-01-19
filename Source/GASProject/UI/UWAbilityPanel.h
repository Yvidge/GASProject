// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UWAbility.h"
#include "Blueprint/UserWidget.h"
#include "Characters/AGPlayerCharacter.h"
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
	TMap<UUWAbility*, TEnumAsByte<EGDAbilityInputID>> AbilitiesMap;


public:

	UFUNCTION(BlueprintCallable)
	void UpdateAbilityCooldown(const TEnumAsByte<EGDAbilityInputID> Binding, const TSubclassOf<UAGGameplayAbilityBase> Class);

protected:

	UFUNCTION()
	void UpdateAbilitySlotBinding(TEnumAsByte<EGDAbilityInputID> Binding, TSubclassOf<UAGGameplayAbilityBase> Class);

	virtual void NativeOnInitialized() override;

	void InitializeAbilitiesMap();

};
