// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/AbilityPickup.h"

#include "Characters/AGPlayerCharacter.h"

// Sets default values
AAbilityPickup::AAbilityPickup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollision"));
	SphereCollision->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AAbilityPickup::BeginPlay()
{
	Super::BeginPlay();
	SphereCollision->OnComponentBeginOverlap.AddDynamic(this, &AAbilityPickup::HandleInteract);
	
}

void AAbilityPickup::HandleInteract(
	UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult& SweepResult)
{

	AAGPlayerCharacter* PlayerCharacter = Cast<AAGPlayerCharacter>(OtherActor);
	if(PlayerCharacter)
	{
		PlayerCharacter->GetAbilitySystemComponent()->GiveAbility(FGameplayAbilitySpec(AbilityClass));
		Destroy();
	}

}


// Called every frame
void AAbilityPickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

