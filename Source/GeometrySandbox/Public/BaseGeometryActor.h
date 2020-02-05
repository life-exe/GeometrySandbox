// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "BaseGeometryActor.generated.h"

UENUM(BlueprintType)
enum class EMovementType : uint8
{
    Sin,
    Static
};

USTRUCT(BlueprintType)
struct FGeometryData
{
    GENERATED_USTRUCT_BODY()

    UPROPERTY(EditAnywhere, Category = "Movement")
    float Amplitude = 50.0f;

    UPROPERTY(EditAnywhere, Category = "Movement")
    float Frequency = 2.0f;

    UPROPERTY(EditAnywhere, Category = "Movement")
    EMovementType MoveType = EMovementType::Static;

    UPROPERTY(EditAnywhere, Category = "Design")
    FLinearColor Color = FLinearColor::Black;

    UPROPERTY(EditAnywhere, Category = "Design")
    float TimerRate = 3.0f;
};

UCLASS()
class GEOMETRYSANDBOX_API ABaseGeometryActor : public AActor
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    ABaseGeometryActor();

    UPROPERTY(VisibleAnywhere)
    UStaticMeshComponent* BaseMesh;

    void SetGeometryData(const FGeometryData& Data) { GeometryData = Data; }

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

    UPROPERTY(EditAnywhere, Category = "Geometry Data")
    FGeometryData GeometryData;

    UPROPERTY(EditAnywhere, Category = "Weapon")
    int32 WeaponsNum = 4;

    UPROPERTY(EditDefaultsOnly, Category = "Stat")
    int32 KillsNum = 7;

    UPROPERTY(EditInstanceOnly, Category = "Health")
    float Health = 34.435235f;

    UPROPERTY(EditAnywhere, Category = "Health")
    bool IsDead = false;

    UPROPERTY(VisibleAnywhere, Category = "Weapon")
    bool HasWeapon = true;

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;

private:
    FVector InitialLocation;
    FTimerHandle TimerHandle;

    const int32 MaxTimerCount = 5;
    int32 TimerCount = 0;

    void HandleMovement();

    void PrintTypes();
    void PrintStringTypes();
    void PrintTransform();

    void SetColor(const FLinearColor& Color);

    void OnTimerFired();
};
