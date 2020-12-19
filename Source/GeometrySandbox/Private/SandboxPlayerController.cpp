// Geometry Sandbox, All Rights Reserved.

#include "SandboxPlayerController.h"
#include "Components/InputComponent.h"
#include "Kismet/GameplayStatics.h"
#include "SandboxPawn.h"
#include "Engine/World.h"

DEFINE_LOG_CATEGORY_STATIC(LogSandboxPlayerController, All, All)

void ASandboxPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();

    if (InputComponent)
    {
        InputComponent->BindAction("ChangePawn", IE_Pressed, this, &ASandboxPlayerController::ChangePawn);
    }
}

void ASandboxPlayerController::BeginPlay()
{
    Super::BeginPlay();

    UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASandboxPawn::StaticClass(), Pawns);
}

void ASandboxPlayerController::ChangePawn()
{
    if (Pawns.Num() <= 1) return;

    ASandboxPawn* CurrentPawn = Cast<ASandboxPawn>(Pawns[CurrentPawnIndex]);
    CurrentPawnIndex = (CurrentPawnIndex + 1) % Pawns.Num();
    if (!CurrentPawn) return;

    UE_LOG(LogSandboxPlayerController, Error, TEXT("Change player pawn"));
    Possess(CurrentPawn);
}
