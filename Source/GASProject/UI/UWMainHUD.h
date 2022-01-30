// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "UWMainHUD.generated.h"

/**
 * 
 */
UCLASS()
class GASPROJECT_API UUWMainHUD : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (BindWidget = "HealthBar"))
	class UProgressBar* HealthBar;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (BindWidgetOptional = "HealthLabel"))
	class UTextBlock* HealthLabel;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (BindWidgetOptional = "MaxHealthLabel"))
	class UTextBlock* MaxHealthLabel;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (BindWidgetOptional = "MoveSpeedLabel"))
	class UTextBlock* MoveSpeedLabel;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (BindWidgetOptional = "IntelligenceLabel"))
	class UTextBlock* IntelligenceLabel;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (BindWidgetOptional = "DamageResistLabel"))
	class UTextBlock* DamageResistLabel;

protected:

	float CachedMaxHealth = 0;
	float CachedHealth = 0;

	virtual void NativeConstruct() override;

	UFUNCTION()
	void UpdateHealthBar();

	UFUNCTION()
	void UpdateHealth(float NewValue, float OldValue);

	UFUNCTION()
	void UpdateMaxHealth(float NewValue, float OldValue);

	UFUNCTION()
	void UpdateMoveSpeed(float NewValue, float OldValue);

	UFUNCTION()
	void UpdateDamageResist(float NewValue, float OldValue);

	UFUNCTION()
	void UpdateIntelligence(float NewValue, float OldValue);

	UFUNCTION(BlueprintImplementableEvent)
	void DamageResponse(float DamageAmount);
	
};
