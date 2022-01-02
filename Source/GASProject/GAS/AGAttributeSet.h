// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "AGAttributeSet.generated.h"

/**
 * 
 */


class UAbilitySystemComponent;

UCLASS()
class GASPROJECT_API UAGAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:

	UAGAttributeSet();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
	FGameplayAttributeData Health;

	GAMEPLAYATTRIBUTE_VALUE_GETTER(Health);
	GAMEPLAYATTRIBUTE_VALUE_SETTER(Health);
	GAMEPLAYATTRIBUTE_VALUE_INITTER(Health);
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(UAGAttributeSet, Health);


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
	FGameplayAttributeData MaxHealth;

	GAMEPLAYATTRIBUTE_VALUE_GETTER(MaxHealth);
	GAMEPLAYATTRIBUTE_VALUE_SETTER(MaxHealth);
	GAMEPLAYATTRIBUTE_VALUE_INITTER(MaxHealth);
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(UAGAttributeSet, MaxHealth);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
	FGameplayAttributeData MoveSpeed;

	GAMEPLAYATTRIBUTE_VALUE_GETTER(MoveSpeed);
	GAMEPLAYATTRIBUTE_VALUE_SETTER(MoveSpeed);
	GAMEPLAYATTRIBUTE_VALUE_INITTER(MoveSpeed);
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(UAGAttributeSet, MoveSpeed);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
	FGameplayAttributeData DamageTaken;

	GAMEPLAYATTRIBUTE_VALUE_GETTER(DamageTaken);
	GAMEPLAYATTRIBUTE_VALUE_SETTER(DamageTaken);
	GAMEPLAYATTRIBUTE_VALUE_INITTER(DamageTaken);
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(UAGAttributeSet, DamageTaken);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
	FGameplayAttributeData DamageResistance;

	GAMEPLAYATTRIBUTE_VALUE_GETTER(DamageResistance);
	GAMEPLAYATTRIBUTE_VALUE_SETTER(DamageResistance);
	GAMEPLAYATTRIBUTE_VALUE_INITTER(DamageResistance);
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(UAGAttributeSet, DamageResistance);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
	FGameplayAttributeData Strength;

	GAMEPLAYATTRIBUTE_VALUE_GETTER(Strength);
	GAMEPLAYATTRIBUTE_VALUE_SETTER(Strength);
	GAMEPLAYATTRIBUTE_VALUE_INITTER(Strength);
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(UAGAttributeSet, Strength);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
	FGameplayAttributeData	Intelligence;

	GAMEPLAYATTRIBUTE_VALUE_GETTER(Intelligence);
	GAMEPLAYATTRIBUTE_VALUE_SETTER(Intelligence);
	GAMEPLAYATTRIBUTE_VALUE_INITTER(Intelligence);
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(UAGAttributeSet, Intelligence);

};
