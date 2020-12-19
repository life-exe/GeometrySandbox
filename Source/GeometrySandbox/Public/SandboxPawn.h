// Geometry Sandbox, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "SandboxPawn.generated.h"

class UCameraComponent;
class UStaticMeshComponent;

UCLASS()
class GEOMETRYSANDBOX_API ASandboxPawn : public APawn
{
    GENERATED_BODY()

public:
    ASandboxPawn();

    UPROPERTY(VisibleAnywhere)
    USceneComponent* SceneComponent;

    UPROPERTY(VisibleAnywhere)
    UStaticMeshComponent* StaticMeshComponent;

    UPROPERTY(VisibleAnywhere)
    UCameraComponent* CameraComponent;

    UPROPERTY(EditAnywhere)
    float Velocity = 300.0f;

    virtual void PossessedBy(AController* NewController) override;
    virtual void UnPossessed() override;

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
    FVector VelocityVector = FVector::ZeroVector;

    void MoveForward(float Amount);
    void MoveRight(float Amount);
};
