// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "GAS/AGAttributeSet.h"
#include "GASProjectCharacter.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FAttributeChangedDelegate, float, NewValue, float, OldValue);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCharacterDiedDelegate, ACharacter*, Character);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDamageTaken, float, DamageAmount);

UENUM(BlueprintType)
enum ECharacterRoleType
{
	None UMETA(DisplayName = "None"),
	Player UMETA(DisplayName = "Player"),
	Frontline UMETA(DisplayName = "Frontline"),
	Backline UMETA(DisplayName = "Backline"),
	Support UMETA(DisplayName = "Support")
};


UCLASS(config=Game)
class AGASProjectCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

	
public:
	AGASProjectCharacter(const class FObjectInitializer& ObjectInitializer);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USceneComponent* ProjectileSpawnPoint;
	
	UPROPERTY(BlueprintReadOnly, Category = AbilitySystem)
	UAbilitySystemComponent* AbilitySystemComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = AbilitySystem, meta = (AllowPrivateAccess = "true"))
	UAGAttributeSet* BaseAttributeSet;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AbilitySystem)
	TArray<TSubclassOf<class UGameplayAbility>> StartupAbilities;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	TEnumAsByte<ECharacterRoleType> CharacterRole;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = AbilitySystem)
	TSubclassOf<UGameplayEffect> StatInitializer;

	UPROPERTY(BlueprintAssignable)
	FAttributeChangedDelegate OnHealthChangedDelegate;

	UPROPERTY(BlueprintAssignable)
	FAttributeChangedDelegate OnMaxHealthChangedDelegate;

	UPROPERTY(BlueprintAssignable)
	FAttributeChangedDelegate OnMoveSpeedChangedDelegate;

	UPROPERTY(BlueprintAssignable)
	FAttributeChangedDelegate OnDamageResistanceChangedDelegate;

	UPROPERTY(BlueprintAssignable)
	FAttributeChangedDelegate OnIntelligenceChangedDelegate;

	UPROPERTY(BlueprintAssignable)
	FCharacterDiedDelegate OnDiedDelegate;

	UPROPERTY(BlueprintAssignable)
	FDamageTaken OnDamageTaken;

protected:

	virtual void BeginPlay() override;

	void InitializeAttributes();

	virtual void HealthChanged(const FOnAttributeChangeData& Data);

	virtual void MaxHealthChanged(const FOnAttributeChangeData& Data);

	virtual void MoveSpeedChanged(const FOnAttributeChangeData& Data);

	virtual void IntelligenceChanged(const FOnAttributeChangeData& Data);

	virtual void DamageResistChanged(const FOnAttributeChangeData& Data);

public:

	UFUNCTION(BlueprintCallable, Category = AbilitySystem)
	float GetHealth() const;

	UFUNCTION(BlueprintCallable, Category = AbilitySystem)
	float GetMaxHealth() const;

	UFUNCTION(BlueprintCallable, Category = AbilitySystem)
	float GetMoveSpeed() const;

	UFUNCTION(BlueprintCallable, Category = AbilitySystem)
	float GetIntelligence() const;

	UFUNCTION(BlueprintCallable, Category = AbilitySystem)
	float GetDamageResistance() const;

	UFUNCTION(BlueprintImplementableEvent)
	void OnHealthChanged(float OldValue, float NewValue);

	UFUNCTION(BlueprintImplementableEvent)
	void OnKilled();

	void NativeOnKilled();

	FORCEINLINE class UAbilitySystemComponent* GetAbilitySystemComponent() const override { return AbilitySystemComponent; }
};

