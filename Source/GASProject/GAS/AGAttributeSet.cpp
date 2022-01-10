// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/AGAttributeSet.h"

void UAGAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

	if(Attribute == GetHealthAttribute())
	{
		NewValue = FMath::Clamp<float>(NewValue, 0, MaxHealth.GetCurrentValue());
	}

}

UAGAttributeSet::UAGAttributeSet()
	:Health(100.0f)
	,MaxHealth(100.0f)
{
}
