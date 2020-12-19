// Geometry Sandbox, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseGeometryActor.h"
#include "GeometryHubActor.generated.h"

USTRUCT(BlueprintType)
struct FGeometryPayload
{
    GENERATED_USTRUCT_BODY()

    UPROPERTY(EditAnywhere)
    TSubclassOf<ABaseGeometryActor> GeometryClass;

    UPROPERTY(EditAnywhere)
    FGeometryData Data;

    UPROPERTY(EditAnywhere)
    FTransform InitialTransform;
};

UCLASS()
class GEOMETRYSANDBOX_API AGeometryHubActor : public AActor
{
    GENERATED_BODY()

public:
    AGeometryHubActor();

protected:
    virtual void BeginPlay() override;

    UPROPERTY(EditAnywhere)
    TSubclassOf<ABaseGeometryActor> GeometryClass;

    UPROPERTY(EditAnywhere)
    TArray<FGeometryPayload> GeometryPayloads;

public:
    virtual void Tick(float DeltaTime) override;

private:
    ABaseGeometryActor* NonePropertyActor;

    UPROPERTY()
    ABaseGeometryActor* PropertyActor;

    void DoActorSpawn1();
    void DoActorSpawn2();
    void DoActorSpawn3();
    void DoActorSpawn4();

    UFUNCTION()
    void OnColorChanged(const FLinearColor& Color, const FString& Name);

    void OnTimerFinished(AActor* Actor);
};
