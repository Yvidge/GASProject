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
	OnHealthChangedDelegate.Broadcast(Data.NewValue, Data.OldValue);
	if(Data.NewValue <= 0)
	{
		OnKilled();
		NativeOnKilled();
	}
}

void AGASProjectCharacter::MaxHealthChanged(const FOnAttributeChangeData& Data)
{
	OnMaxHealthChangedDelegate.Broadcast(Data.NewValue, Data.OldValue);
}

void AGASProjectCharacter::MoveSpeedChanged(const FOnAttributeChangeData& Data)
{
	Cast<UCharacterMovementComponent>(GetMovementComponent())->MaxWalkSpeed = Data.NewValue;
	OnMoveSpeedChangedDelegate.Broadcast(Data.NewValue, Data.OldValue);
}

void AGASProjectCharacter::IntelligenceChanged(const FOnAttributeChangeData& Data)
{
	OnIntelligenceChangedDelegate.Broadcast(Data.NewValue, Data.OldValue);
}

void AGASProjectCharacter::DamageResistChanged(const FOnAttributeChangeData& Data)
{
	OnDamageResistanceChangedDelegate.Broadcast(Data.NewValue, Data.OldValue);
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

float AGASProjectCharacter::GetIntelligence() const
{
	return BaseAttributeSet->GetIntelligence();
}

float AGASProjectCharacter::GetDamageResistance() const
{
	return  BaseAttributeSet->GetDamageResistance();
}

void AGASProjectCharacter::NativeOnKilled()
{
	OnDiedDelegate.Broadcast(this);
	//Destroy();
}


void AGASProjectCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(BaseAttributeSet->GetHealthAttribute()).AddUObject(this, &AGASProjectCharacter::HealthChanged);
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(BaseAttributeSet->GetMaxHealthAttribute()).AddUObject(this, &AGASProjectCharacter::MaxHealthChanged);
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(BaseAttributeSet->GetMoveSpeedAttribute()).AddUObject(this, &AGASProjectCharacter::MoveSpeedChanged);

		for (auto Ability : StartupAbilities)
		{
			if (Ability)
			{
				AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(Ability.GetDefaultObject(), 1, 0));
				AbilitySystemComponent->InitAbilityActorInfo(this, this);
			}
		}
	}

	GetWorldTimerManager().SetTimerForNextTick(this, &AGASProjectCharacter::InitializeAttributes);


}

void AGASProjectCharacter::InitializeAttributes()
{
	if (StatInitializer && AbilitySystemComponent) {
		FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();
		EffectContext.AddSourceObject(this);

		FGameplayEffectSpecHandle NewHandle = AbilitySystemComponent->MakeOutgoingSpec(StatInitializer, 1.0f, EffectContext);
		if (NewHandle.IsValid())
		{
			FActiveGameplayEffectHandle ActiveGEHandle = AbilitySystemComponent->ApplyGameplayEffectSpecToTarget(*NewHandle.Data.Get(), AbilitySystemComponent);
		}
	}
}
