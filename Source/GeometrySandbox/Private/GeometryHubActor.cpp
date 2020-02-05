// Fill out your copyright notice in the Description page of Project Settings.


#include "GeometryHubActor.h"
#include "Engine/World.h"

// Sets default values
AGeometryHubActor::AGeometryHubActor()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AGeometryHubActor::BeginPlay()
{
    Super::BeginPlay();

    DoActorSpawn1();
    DoActorSpawn2();
    DoActorSpawn3();
}

void AGeometryHubActor::DoActorSpawn1()
{
    UWorld* World = GetWorld();
    if (World)
    {
        for (int32 i = 0; i < 10; ++i)
        {
            const FTransform GeometryTransform = FTransform(FRotator::ZeroRotator, FVector(0.0f, 300.0f * i, 300.0f));
            ABaseGeometryActor* Geometry = World->SpawnActor<ABaseGeometryActor>(GeometryClass, GeometryTransform);

            if (Geometry)
            {
                FGeometryData Data;
                Data.MoveType = FMath::RandBool() ? EMovementType::Static : EMovementType::Sin;
                Geometry->SetGeometryData(Data);
            }
        }
    }
}

void AGeometryHubActor::DoActorSpawn2()
{
    UWorld* World = GetWorld();
    if (World)
    {
        for (int32 i = 0; i < 10; ++i)
        {
            const FTransform GeometryTransform = FTransform(FRotator::ZeroRotator, FVector(0.0f, 300.0f * i, 700.0f));
            ABaseGeometryActor* Geometry = World->SpawnActorDeferred<ABaseGeometryActor>(GeometryClass, GeometryTransform);

            if (Geometry)
            {
                FGeometryData Data;
                Data.Color = FLinearColor::MakeRandomColor();
                Geometry->SetGeometryData(Data);
                Geometry->FinishSpawning(GeometryTransform);
            }
        }
    }
}

void AGeometryHubActor::DoActorSpawn3()
{
    UWorld* World = GetWorld();
    if (World)
    {
        for (const FGeometryPayload Payload : GeometryPayloads)
        {
            ABaseGeometryActor* Geometry = World->SpawnActorDeferred<ABaseGeometryActor>(Payload.GeometryClass, Payload.InitialTransform);

            if (Geometry)
            {
                Geometry->SetGeometryData(Payload.Data);
                Geometry->FinishSpawning(Payload.InitialTransform);
            }
        }
    }
}

// Called every frame
void AGeometryHubActor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}
