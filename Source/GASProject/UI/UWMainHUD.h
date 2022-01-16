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


protected:

	virtual void NativeConstruct() override;

	UFUNCTION()
	void UpdateHealthBar();

	UFUNCTION()
	void UpdateHealth(float NewValue, float OldValue);

	UFUNCTION()
	void UpdateMaxHealth(float NewValue, float OldValue);

	float CachedMaxHealth = 0;
	float CachedHealth = 0;
};
