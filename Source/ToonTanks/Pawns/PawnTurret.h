// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PawnBase.h"
#include "PawnTank.h"

#include "PawnTurret.generated.h"

class APawnTank;

/**
 * 
 */
UCLASS()
class TOONTANKS_API APawnTurret : public APawnBase
{
    GENERATED_BODY()
public:
    APawnTurret();

    // Called every frame
    virtual void Tick(float DeltaTime) override;
protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

private:

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Combat", meta = (AllowPrivateAccess="true"))
    float FireRate = 2.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Combat", meta = (AllowPrivateAccess="true"))
    float FireRange = 1000.0f;

    FTimerHandle FireRateTimerHandle;

    APawnTank* PlayerPawn;


    void FireIfPossible();

    float GetPlayerDistance() const;

    void RotateTurretIfEnemyInRange();
};
