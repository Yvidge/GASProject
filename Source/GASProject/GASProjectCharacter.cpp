// Copyright Epic Games, Inc. All Rights Reserved.

#include "GASProjectCharacter.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
//////////////////////////////////////////////////////////////////////////
// AGASProjectCharacter

AGASProjectCharacter::AGASProjectCharacter()
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
}

void AGASProjectCharacter::MoveSpeedChanged(const FOnAttributeChangeData& Data)
{
	Cast<UCharacterMovementComponent>(GetMovementComponent())->MaxWalkSpeed = Data.NewValue;
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
