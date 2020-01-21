// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseGeometryActor.h"
#include "Engine/Engine.h"

DEFINE_LOG_CATEGORY_STATIC(LogBaseGeometry, All, All)

// Sets default values
ABaseGeometryActor::ABaseGeometryActor()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>("BaseMesh");
    SetRootComponent(BaseMesh);
}

// Called when the game starts or when spawned
void ABaseGeometryActor::BeginPlay()
{
    Super::BeginPlay();

    InitialLocation = GetActorLocation();

    // printTransform();
    // printStringTypes();
    // printTypes();
}

// Called every frame
void ABaseGeometryActor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // z = z0 + amplitude * sin(freq * t);
    FVector CurrentLocation = GetActorLocation();
    float time = GetWorld()->GetTimeSeconds();
    CurrentLocation.Z = InitialLocation.Z + Amplitude * FMath::Sin(Frequency * time);

    SetActorLocation(CurrentLocation);
}

void ABaseGeometryActor::printTypes()
{
    UE_LOG(LogBaseGeometry, Warning, TEXT("Actor name %s"), *GetName());
    UE_LOG(LogBaseGeometry, Warning, TEXT("Weapons num: %d, kills num: %i"), WeaponsNum, KillsNum);
    UE_LOG(LogBaseGeometry, Warning, TEXT("Health: %f"), Health);
    UE_LOG(LogBaseGeometry, Warning, TEXT("IsDead: %d"), IsDead);
    UE_LOG(LogBaseGeometry, Warning, TEXT("HasWeapon: %d"), static_cast<int>(HasWeapon));
}

void ABaseGeometryActor::printStringTypes()
{
    FString Name = "John Connor";
    UE_LOG(LogBaseGeometry, Display, TEXT("Name: %s"), *Name);

    FString WeaponsNumStr = "Weapons num = " + FString::FromInt(WeaponsNum);
    FString HealthStr = "Health = " + FString::SanitizeFloat(Health);
    FString IsDeadStr = "Is dead = " + FString(IsDead ? "true" : "false");

    FString Stat = FString::Printf(TEXT(" \n == All Stat == \n %s \n %s \n %s "), *WeaponsNumStr, *HealthStr, *IsDeadStr);
    UE_LOG(LogBaseGeometry, Warning, TEXT("%s"), *Stat);

    GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, Name);
    GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, Stat, true, FVector2D(1.5f, 1.5f));
}

void ABaseGeometryActor::printTransform()
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
