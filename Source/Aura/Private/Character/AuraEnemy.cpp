// Copyright by Salih Kayatemir


#include "Character/AuraEnemy.h"
#include "DrawDebugHelpers.h"
#include "Aura/Aura.h"

AAuraEnemy::AAuraEnemy()
{
    PrimaryActorTick.bCanEverTick = true;
    GetMesh()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
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

void AAuraEnemy::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}
