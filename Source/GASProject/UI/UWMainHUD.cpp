// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/UWMainHUD.h"

#include "GASProjectCharacter.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"

void UUWMainHUD::NativeConstruct()
{
	//Super::NativeConstruct();

	AGASProjectCharacter* PlayerCharacter = Cast<AGASProjectCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));

	if(PlayerCharacter)
	{
		PlayerCharacter->OnHealthChangedDelegate.AddDynamic(this, &UUWMainHUD::UpdateHealth);
		PlayerCharacter->OnMaxHealthChangedDelegate.AddDynamic(this, &UUWMainHUD::UpdateMaxHealth);
		PlayerCharacter->OnMoveSpeedChangedDelegate.AddDynamic(this, &UUWMainHUD::UpdateMoveSpeed);
		PlayerCharacter->OnIntelligenceChangedDelegate.AddDynamic(this, &UUWMainHUD::UpdateIntelligence);
		PlayerCharacter->OnDamageResistanceChangedDelegate.AddDynamic(this, &UUWMainHUD::UpdateDamageResist);
		PlayerCharacter->OnDamageTaken.AddDynamic(this, &UUWMainHUD::DamageResponse);
	}

}

void UUWMainHUD::UpdateHealthBar()
{
	HealthBar->SetPercent(CachedHealth / CachedMaxHealth);
}

void UUWMainHUD::UpdateHealth(float NewValue, float OldValue)
{
	CachedHealth = NewValue;
	UpdateHealthBar();
	if (HealthLabel)
	{
		HealthLabel->SetText(FText::FromString(FString::FromInt(NewValue)));
	}
}

void UUWMainHUD::UpdateMaxHealth(float NewValue, float OldValue)
{
	CachedMaxHealth = NewValue;
	UpdateHealthBar();
	if (MaxHealthLabel)
	{
		MaxHealthLabel->SetText(FText::FromString(FString::FromInt(NewValue)));
	}
}

void UUWMainHUD::UpdateMoveSpeed(float NewValue, float OldValue)
{
	if(MoveSpeedLabel)
	{
		MoveSpeedLabel->SetText(FText::FromString(FString::FromInt(NewValue)));
	}
}

void UUWMainHUD::UpdateDamageResist(float NewValue, float OldValue)
{
	if (DamageResistLabel)
	{
		DamageResistLabel->SetText(FText::FromString(FString::FromInt(NewValue)));
	}
}

void UUWMainHUD::UpdateIntelligence(float NewValue, float OldValue)
{
	if (IntelligenceLabel)
	{
		IntelligenceLabel->SetText(FText::FromString(FString::FromInt(NewValue)));
	}
}
