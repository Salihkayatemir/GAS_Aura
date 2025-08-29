// Copyright by Salih Kayatemir


#include "Character/AuraCharacterBase.h"



AAuraCharacterBase::AAuraCharacterBase()
{
	PrimaryActorTick.bCanEverTick = false;

	WeaponMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMesh"));
	WeaponMeshComponent->SetupAttachment(GetMesh(), FName("WeaponSocket"));
	WeaponMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AAuraCharacterBase::BeginPlay()
{
	Super::BeginPlay();
}

UAbilitySystemComponent * AAuraCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}