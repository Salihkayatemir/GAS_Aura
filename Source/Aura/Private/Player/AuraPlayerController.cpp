// Copyright by Salih Kayatemir


#include "Player/AuraPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Interaction/EnemyInterface.h"

AAuraPlayerController::AAuraPlayerController()
{
    bReplicates = true; // Enable replication for this player controller. 
}

void AAuraPlayerController::BeginPlay()
{
	Super::BeginPlay();

    check(AuraContext);
    UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()); // Get the enhanced input subsystem
    check(Subsystem);
    Subsystem->AddMappingContext(AuraContext, 0); // Add the mapping context for the Aura input actions


    bShowMouseCursor = true;
    DefaultMouseCursor = EMouseCursor::Crosshairs;

    FInputModeGameAndUI InputModeData;
    InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock); // Do not lock the mouse to the viewport
    InputModeData.SetHideCursorDuringCapture(false); // Show the cursor when the UI is captured
    SetInputMode(InputModeData); // Set the input mode to the new data
}

void AAuraPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	CursorTrace();
}

void AAuraPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();

    UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);

    EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AAuraPlayerController::Move); // Bind the move action to the Move function

}

void AAuraPlayerController::Move(const FInputActionValue& InputActionValue)
{
    const FVector2D MovementVector = InputActionValue.Get<FVector2D>(); // Get the movement vector from the input action value

    APawn* ControlledPawn = GetPawn(); // Get the controlled pawn
    if (ControlledPawn)
    {
        const FRotator Rotation = GetControlRotation(); // Get the control rotation
        const FRotator YawRotation(0, Rotation.Yaw, 0); // Get the yaw rotation of the controller

        const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X); // Get the forward direction
        const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y); // Get the right direction

        ControlledPawn->AddMovementInput(ForwardDirection, MovementVector.Y); // Add movement input in the forward direction
        ControlledPawn->AddMovementInput(RightDirection, MovementVector.X); // Add movement input in the right direction
    }
}

void AAuraPlayerController::CursorTrace()
{
    
    FHitResult CursorHitResult;
    GetHitResultUnderCursor(ECC_Visibility, false, CursorHitResult);
    if (!CursorHitResult.bBlockingHit) return;

    LastActor = ThisActor; // Mouse'ın değdiği şuan ki aktörü son aktöre eşitledik. 
    ThisActor = CursorHitResult.GetActor(); // Mouse'ın değdiği şuan ki aktörü bu aktöre eşitledik.

    if (LastActor == nullptr && ThisActor != nullptr) // Highlight this actor
    {
        ThisActor->HighlightActor();
    }else if (LastActor != nullptr && ThisActor == nullptr) // Unhighlight the last actor
    {
        LastActor->UnHighlightActor();
    }else if (LastActor != nullptr && ThisActor != nullptr && LastActor != ThisActor) // Unhighlight the last actor, Highlight the new actor
    {
        LastActor->UnHighlightActor();
        ThisActor->HighlightActor();
    }else if (LastActor != nullptr && ThisActor != nullptr && LastActor == ThisActor)
    {
        ThisActor->HighlightActor();
    }
}