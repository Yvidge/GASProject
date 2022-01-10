// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "GAS/AGAttributeSet.h"
#include "GASProjectCharacter.generated.h"

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
	//AGASProjectCharacter();
	UPROPERTY(BlueprintReadOnly, Category = AbilitySystem)
	UAbilitySystemComponent* AbilitySystemComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = AbilitySystem, meta = (AllowPrivateAccess = "true"))
	UAGAttributeSet* BaseAttributeSet;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AbilitySystem)
	TArray<TSubclassOf<class UGameplayAbility>> StartupAbilities;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	TEnumAsByte<ECharacterRoleType> CharacterRole;

protected:

	virtual void BeginPlay() override;

	virtual void HealthChanged(const FOnAttributeChangeData& Data);

	virtual void MoveSpeedChanged(const FOnAttributeChangeData& Data);

public:

	UFUNCTION(BlueprintCallable, Category = AbilitySystem)
	float GetHealth() const;

	UFUNCTION(BlueprintCallable, Category = AbilitySystem)
	float GetMaxHealth() const;

	UFUNCTION(BlueprintCallable, Category = AbilitySystem)
	float GetMoveSpeed() const;

	UFUNCTION(BlueprintImplementableEvent)
	void OnHealthChanged(float OldValue, float NewValue);

	UFUNCTION(BlueprintImplementableEvent)
	void OnKilled();

	void NativeOnKilled();

	FORCEINLINE class UAbilitySystemComponent* GetAbilitySystemComponent() const override { return AbilitySystemComponent; }
};

