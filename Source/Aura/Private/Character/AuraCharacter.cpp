// Copyright by Salih Kayatemir


#include "Character/AuraCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "AuraCharacter.h"

AAuraCharacter::AAuraCharacter()
{
    
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArmComponent->SetupAttachment(GetRootComponent());
	SpringArmComponent->TargetArmLength = 750.f;
	SpringArmComponent->SetRelativeRotation(FRotator(-45.f, 0.f, 0.f));

    SpringArmComponent->bEnableCameraLag = true;
    SpringArmComponent->CameraLagSpeed = 5.f;

    SpringArmComponent->bInheritPitch = false;
    SpringArmComponent->bInheritRoll = false;
    SpringArmComponent->bInheritYaw = false;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(SpringArmComponent);

    GetCharacterMovement()->bOrientRotationToMovement = true; // Karakterin hareket yönüne doğru dönmesini sağlar.
    GetCharacterMovement()->RotationRate = FRotator(0.f, 400.f, 0.f); // Karakterin dönebilme hızı.
    GetCharacterMovement()->bConstrainToPlane = true; // Top-down veya side-scroller oyunlarında karakterin yanlış eksene kaymasını engeller. Fiziksel hareketleri de bu düzlemle sınırlar (örneğin çarpışmalar, kaymalar vs.).
    GetCharacterMovement()->bSnapToPlaneAtStart = true; // Oyun başladığında karakterin pozisyonunu en yakın düzleme çeker. Böylece karakter “havada asılı” kalmaz veya yanlış eksende spawn olmaz.

    
    bUseControllerRotationYaw = false; // 
    bUseControllerRotationPitch = false;
    bUseControllerRotationRoll = false;
}

void AAuraCharacter::BeginPlay()
{
    Super::BeginPlay();
    
}

void AAuraCharacter::PossessedBy(AController *NewController)
{
    Super::PossessedBy(NewController);

    // Initialize ability actor info for the server
    InitAbilityActorInfo();
}

void AAuraCharacter::OnRep_PlayerState()
{
    Super::OnRep_PlayerState();
    // Initialize ability actor info for the client
    InitAbilityActorInfo();
}

void AAuraCharacter::InitAbilityActorInfo()
{
    AuraPlayerState* AuraPlayerState = GetPlayerState<AuraPlayerState>();
    check(AuraPlayerState);
    AuraPlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(AuraPlayerState, this);
    AbilitySystemComponent = AuraPlayerState->GetAbilitySystemComponent();
    AttributeSet = AuraPlayerState->GetAttributeSet();
}