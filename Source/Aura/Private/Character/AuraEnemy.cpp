// Copyright by Salih Kayatemir


#include "Character/AuraEnemy.h"
#include "DrawDebugHelpers.h"
#include "Aura/Aura.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"

AAuraEnemy::AAuraEnemy()
{
    PrimaryActorTick.bCanEverTick = true;
    GetMesh()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);

	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystem"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

	AttributeSet = CreateDefaultSubobject<UAuraAttributeSet>(TEXT("AttributeSet"));
}

void AAuraEnemy::BeginPlay()
{
    Super::BeginPlay();
    AbilitySystemComponent->InitAbilityActorInfo(this, this);
    
}

void AAuraEnemy::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void AAuraEnemy::HighlightActor()
{
    GetMesh()->SetRenderCustomDepth(true);
    GetMesh()->SetCustomDepthStencilValue(CUSTOM_DEPTH_STENCIL_VALUE);
    WeaponMeshComponent->SetRenderCustomDepth(true);
    WeaponMeshComponent->SetCustomDepthStencilValue(CUSTOM_DEPTH_STENCIL_VALUE);
}
    
void AAuraEnemy::UnHighlightActor()
{
    GetMesh()->SetRenderCustomDepth(false);
    WeaponMeshComponent->SetRenderCustomDepth(false);
}