// Copyright Epic Games, Inc. All Rights Reserved.

#include "GASProjectCharacter.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Characters/AGCharacterMovementComponent.h"
//////////////////////////////////////////////////////////////////////////
// AGASProjectCharacter

AGASProjectCharacter::AGASProjectCharacter(const class FObjectInitializer& ObjectInitializer):
	Super(ObjectInitializer.SetDefaultSubobjectClass<UAGCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;


	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));

	BaseAttributeSet = CreateDefaultSubobject<UAGAttributeSet>(TEXT("AttributeSet"));
}

void AGASProjectCharacter::HealthChanged(const FOnAttributeChangeData& Data)
{
	OnHealthChanged(Data.OldValue, Data.NewValue);

	if(Data.NewValue <= 0)
	{
		OnKilled();
		NativeOnKilled();
	}
}

void AGASProjectCharacter::MoveSpeedChanged(const FOnAttributeChangeData& Data)
{
	Cast<UCharacterMovementComponent>(GetMovementComponent())->MaxWalkSpeed = Data.NewValue;
}

float AGASProjectCharacter::GetHealth() const
{
	return BaseAttributeSet->GetHealth();
}

float AGASProjectCharacter::GetMaxHealth() const
{
	return BaseAttributeSet->GetMaxHealth();
}

float AGASProjectCharacter::GetMoveSpeed() const
{
	return BaseAttributeSet->GetMoveSpeed();
}

void AGASProjectCharacter::NativeOnKilled()
{
	Destroy();
}


void AGASProjectCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (AbilitySystemComponent)
	{
		for (auto Ability : StartupAbilities)
		{
			if (Ability)
			{
				AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(Ability.GetDefaultObject(), 1, 0));
				AbilitySystemComponent->InitAbilityActorInfo(this, this);
			}
		}
	}

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(BaseAttributeSet->GetHealthAttribute()).AddUObject(this, &AGASProjectCharacter::HealthChanged);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(BaseAttributeSet->GetMoveSpeedAttribute()).AddUObject(this, &AGASProjectCharacter::MoveSpeedChanged);


}
