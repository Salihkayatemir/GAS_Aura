// Copyright by Salih Kayatemir


#include "Player/AuraPlayerState.h"
#include "AbilitySystemComponent.h"
#include "AuraAttributeSet.h"
#include "AuraPlayerState.h"

AAuraPlayerState::AAuraPlayerState()
{
    AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystem"));
    AbilitySystemComponent->SetIsReplicated(true);
    
    AttributeSet = CreateDefaultSubobject<UAuraAttributeSet>(TEXT("AttributeSet"));

    NetUpdateFrequency = 100.0f;

}

UAbilitySystemComponent * AAuraPlayerState::GetAbilitySystemComponent() const
{
    return AbilitySystemComponent;
}