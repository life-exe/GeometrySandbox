// Geometry Sandbox, All Rights Reserved.

#include "BaseGeometryActor.h"
#include "Engine/Engine.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "TimerManager.h"
#include "Components/StaticMeshComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogBaseGeometry, All, All)

ABaseGeometryActor::ABaseGeometryActor()
{
    PrimaryActorTick.bCanEverTick = true;

    BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>("BaseMesh");
    SetRootComponent(BaseMesh);
}

void ABaseGeometryActor::BeginPlay()
{
    Super::BeginPlay();

    InitialLocation = GetActorLocation();

    // PrintTransform();
    // PrintStringTypes();
    // PrintTypes();

    SetColor(GeometryData.Color);

    GetWorldTimerManager().SetTimer(TimerHandle, this, &ABaseGeometryActor::OnTimerFired, GeometryData.TimerRate, true);
}

void ABaseGeometryActor::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    UE_LOG(LogBaseGeometry, Error, TEXT("Actor is dead %s"), *GetName());
    Super::EndPlay(EndPlayReason);
}

void ABaseGeometryActor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    HandleMovement();
}

void ABaseGeometryActor::HandleMovement()
{
    switch (GeometryData.MoveType)
    {
        case EMovementType::Sin:
        {
            // z = z0 + amplitude * sin(freq * t);
            FVector CurrentLocation = GetActorLocation();
            if (GetWorld())
            {
                float Time = GetWorld()->GetTimeSeconds();
                CurrentLocation.Z = InitialLocation.Z + GeometryData.Amplitude * FMath::Sin(GeometryData.Frequency * Time);

                SetActorLocation(CurrentLocation);
            }
        }
        break;

        case EMovementType::Static: break;
        default: break;
    }
}

void ABaseGeometryActor::PrintTypes()
{
    UE_LOG(LogBaseGeometry, Warning, TEXT("Actor name %s"), *GetName());
    UE_LOG(LogBaseGeometry, Warning, TEXT("Weapons num: %d, kills num: %i"), WeaponsNum, KillsNum);
    UE_LOG(LogBaseGeometry, Warning, TEXT("Health: %f"), Health);
    UE_LOG(LogBaseGeometry, Warning, TEXT("IsDead: %d"), IsDead);
    UE_LOG(LogBaseGeometry, Warning, TEXT("HasWeapon: %d"), static_cast<int>(HasWeapon));
}

void ABaseGeometryActor::PrintStringTypes()
{
    FString Name = "John Connor";
    UE_LOG(LogBaseGeometry, Display, TEXT("Name: %s"), *Name);

    FString WeaponsNumStr = "Weapons num = " + FString::FromInt(WeaponsNum);
    FString HealthStr = "Health = " + FString::SanitizeFloat(Health);
    FString IsDeadStr = "Is dead = " + FString(IsDead ? "true" : "false");

    FString Stat = FString::Printf(TEXT(" \n == All Stat == \n %s \n %s \n %s "), *WeaponsNumStr, *HealthStr, *IsDeadStr);
    UE_LOG(LogBaseGeometry, Warning, TEXT("%s"), *Stat);

    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, Name);
        GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, Stat, true, FVector2D(1.5f, 1.5f));
    }
}

void ABaseGeometryActor::PrintTransform()
{
    FTransform Transform = GetActorTransform();
    FVector Location = Transform.GetLocation();
    FRotator Rotation = Transform.Rotator();
    FVector Scale = Transform.GetScale3D();

    UE_LOG(LogBaseGeometry, Warning, TEXT("Actor name %s"), *GetName());
    UE_LOG(LogBaseGeometry, Warning, TEXT("Transform %s"), *Transform.ToString());
    UE_LOG(LogBaseGeometry, Warning, TEXT("Location %s"), *Location.ToString());
    UE_LOG(LogBaseGeometry, Warning, TEXT("Rotation %s"), *Rotation.ToString());
    UE_LOG(LogBaseGeometry, Warning, TEXT("Scale %s"), *Scale.ToString());

    UE_LOG(LogBaseGeometry, Error, TEXT("Human transform %s"), *Transform.ToHumanReadableString());
}

void ABaseGeometryActor::SetColor(const FLinearColor& Color)
{
    if (!BaseMesh) return;
    UMaterialInstanceDynamic* DynMaterial = BaseMesh->CreateAndSetMaterialInstanceDynamic(0);
    if (DynMaterial)
    {
        DynMaterial->SetVectorParameterValue("Color", Color);
    }
}

void ABaseGeometryActor::OnTimerFired()
{
    if (++TimerCount <= MaxTimerCount)
    {
        const FLinearColor NewColor = FLinearColor::MakeRandomColor();
        UE_LOG(LogBaseGeometry, Display, TEXT("TimerCount: %i, Color to set up: %s"), TimerCount, *NewColor.ToString());
        SetColor(NewColor);
        OnColorChanged.Broadcast(NewColor, GetName());
    }
    else
    {
        UE_LOG(LogBaseGeometry, Warning, TEXT("Timer has been stopped!"));
        GetWorldTimerManager().ClearTimer(TimerHandle);
        OnTimerFinished.Broadcast(this);
    }
}
