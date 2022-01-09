// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "GAS/AGAttributeSet.h"
#include "GASProjectCharacter.generated.h"

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

protected:

	virtual void BeginPlay() override;

	virtual void HealthChanged(const FOnAttributeChangeData& Data);

	virtual void MoveSpeedChanged(const FOnAttributeChangeData& Data);

public:

	UFUNCTION(BlueprintImplementableEvent)
	void OnHealtChanged(float OldValue, float NewValue);

	UFUNCTION(BlueprintImplementableEvent)
	void OnKilled();

	void NativeOnKilled();

	FORCEINLINE class UAbilitySystemComponent* GetAbilitySystemComponent() const override { return AbilitySystemComponent; }
};

