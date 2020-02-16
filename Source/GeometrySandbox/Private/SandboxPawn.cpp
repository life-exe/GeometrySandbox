// Geometry Sandbox, All Rights Reserved.

#include "SandboxPawn.h"
#include "Components/InputComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Camera/CameraComponent.h"
#include "Gameframework/Controller.h"

DEFINE_LOG_CATEGORY_STATIC(LogSandboxPawn, All, All)

ASandboxPawn::ASandboxPawn()
{
    PrimaryActorTick.bCanEverTick = true;

    SceneComponent = CreateDefaultSubobject<USceneComponent>("SceneComponent");
    SetRootComponent(SceneComponent);

    StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshComponent");
    StaticMeshComponent->SetupAttachment(GetRootComponent());

    CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
    CameraComponent->SetupAttachment(GetRootComponent());
}

void ASandboxPawn::BeginPlay()
{
    Super::BeginPlay();
}

void ASandboxPawn::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (!VelocityVector.IsZero())
    {
        const FVector NewLocation = GetActorLocation() + Velocity * DeltaTime * VelocityVector;
        SetActorLocation(NewLocation);
        VelocityVector = FVector::ZeroVector;
    }
}

void ASandboxPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    if (PlayerInputComponent)
    {
        PlayerInputComponent->BindAxis("MoveForward", this, &ASandboxPawn::MoveForward);
        PlayerInputComponent->BindAxis("MoveRight", this, &ASandboxPawn::MoveRight);
    }
}

void ASandboxPawn::MoveForward(float Amount)
{
    VelocityVector.X = Amount;
}

void ASandboxPawn::MoveRight(float Amount)
{
    VelocityVector.Y = Amount;
}

void ASandboxPawn::PossessedBy(AController* NewController)
{
    Super::PossessedBy(NewController);

    if (!NewController) return;
    UE_LOG(LogSandboxPawn, Error, TEXT("%s possessed by %s"), *GetName(), *NewController->GetName());
}

void ASandboxPawn::UnPossessed()
{
    Super::UnPossessed();

    UE_LOG(LogSandboxPawn, Warning, TEXT("%s unpossessed"), *GetName());
}
