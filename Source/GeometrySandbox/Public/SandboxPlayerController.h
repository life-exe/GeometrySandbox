// Geometry Sandbox, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SandboxPlayerController.generated.h"

UCLASS()
class GEOMETRYSANDBOX_API ASandboxPlayerController : public APlayerController
{
    GENERATED_BODY()

protected:
    virtual void SetupInputComponent() override;
    virtual void BeginPlay() override;

private:
    UPROPERTY()
    TArray<AActor*> Pawns;

    int32 CurrentPawnIndex = 0;

    void ChangePawn();
};
