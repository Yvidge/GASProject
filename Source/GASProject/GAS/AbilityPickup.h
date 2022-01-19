// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AGGameplayAbilityBase.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "AbilityPickup.generated.h"

UCLASS()
class GASPROJECT_API AAbilityPickup : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAbilityPickup();

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	USphereComponent* SphereCollision;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Ability)
	TSubclassOf<UAGGameplayAbilityBase> AbilityClass;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void HandleInteract(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
