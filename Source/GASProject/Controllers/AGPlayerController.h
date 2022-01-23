// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/AGPlayerCharacter.h"
#include "GameFramework/PlayerController.h"
#include "GAS/AGGameplayAbilityBase.h"
#include "UI/UWAbilityBook.h"
#include "AGPlayerController.generated.h"

class UUWMainHUD;
/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FAbilityBindingChaged, TEnumAsByte<EGDAbilityInputID>, InputBinding, TSubclassOf<UAGGameplayAbilityBase>, NewAbility);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FAbilityBindingUsed, TEnumAsByte<EGDAbilityInputID>, InputBinding, TSubclassOf<UAGGameplayAbilityBase>, NewAbility);

UCLASS()
class GASPROJECT_API AAGPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadOnly)
	UUWMainHUD* HUDWidget;

	UPROPERTY(BlueprintReadOnly)
	UUWAbilityBook* AbilityBookWidget;

	UPROPERTY(EditDefaultsOnly, Category="UI")
	TSubclassOf<UUWMainHUD> HUDWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UUWAbilityBook> AbilityBookWidgetClass;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TMap<EGDAbilityInputID, TSubclassOf<UAGGameplayAbilityBase>> AbilityInputBindings;

	virtual void BeginPlay() override;

public:

	UPROPERTY(BlueprintAssignable)
	FAbilityBindingChaged OnAbilityBindingChanged;

	UPROPERTY(BlueprintAssignable)
	FAbilityBindingUsed OnAbilityBindingUsed;

	UFUNCTION(BlueprintCallable)
	void OpenAbilityBook();

	UFUNCTION(BlueprintCallable)
	void CloseAbilityBook();

	UFUNCTION()
	void UpdateAbilityBinding(const TEnumAsByte<EGDAbilityInputID> InputBind, const TSubclassOf<UAGGameplayAbilityBase> AbilityBind);

	UFUNCTION(BlueprintCallable)
	void UseAbilityByInputBinding(const TEnumAsByte<EGDAbilityInputID> InputBind);

	UFUNCTION(BlueprintCallable)
	TSubclassOf<UAGGameplayAbilityBase> GetAbilityByBinding(const TEnumAsByte<EGDAbilityInputID> InputBind);

};
