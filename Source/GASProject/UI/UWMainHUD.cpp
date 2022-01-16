// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/UWMainHUD.h"

#include "GASProjectCharacter.h"
#include "Kismet/GameplayStatics.h"

void UUWMainHUD::NativeConstruct()
{
	//Super::NativeConstruct();

	AGASProjectCharacter* PlayerCharacter = Cast<AGASProjectCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));

	if(PlayerCharacter)
	{
		PlayerCharacter->OnHealthChangedDelegate.AddDynamic(this, &UUWMainHUD::UpdateHealth);
		PlayerCharacter->OnMaxHealthChangedDelegate.AddDynamic(this, &UUWMainHUD::UpdateMaxHealth);
	}

}

void UUWMainHUD::UpdateHealthBar()
{
	HealthBar->SetPercent(CachedHealth / CachedMaxHealth);
	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, FString::Printf(TEXT("%f / %f"), CachedHealth, CachedMaxHealth));
}

void UUWMainHUD::UpdateHealth(float NewValue, float OldValue)
{
	CachedHealth = NewValue;
	UpdateHealthBar();
}

void UUWMainHUD::UpdateMaxHealth(float NewValue, float OldValue)
{
	CachedMaxHealth = NewValue;
	UpdateHealthBar();
}
