// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/AGCharacterMovementComponent.h"
#include "GASProjectCharacter.h"

float UAGCharacterMovementComponent::GetMaxSpeed() const
{
	AGASProjectCharacter* Owner = Cast<AGASProjectCharacter>(GetOwner());
	if(!Owner)
	{
		return Super::GetMaxSpeed();
	}
	if (Owner->GetAbilitySystemComponent()->HasMatchingGameplayTag(FGameplayTag::RequestGameplayTag(FName("State.Debuff.Stun"))))
	{
		return 0.0f;
	}
	return Super::GetMaxSpeed();
}
