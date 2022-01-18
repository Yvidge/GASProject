// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "GAS/AGGameplayAbilityBase.h"
#include "UWAbilityBookSlot.generated.h"

class UUWAbilityBookRow;
/**
 * 
 */
UCLASS()
class GASPROJECT_API UUWAbilityBookSlot : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (BindWidget = "AbilityIcon"))
	UImage* AbilityIcon;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (BindWidget = "SelectButton"))
	UButton* SelectButton;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Ability")
	TSubclassOf<UAGGameplayAbilityBase> AbilityClass;

	UPROPERTY(BlueprintReadOnly)
	UUWAbilityBookRow* OwnerRow;

protected:

	virtual void NativeOnInitialized() override;

	UFUNCTION()
	void HandleSlotSelection();
};
