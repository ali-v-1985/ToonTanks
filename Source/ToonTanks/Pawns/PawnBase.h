// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"

#include "PawnBase.generated.h"

class UCapsuleComponent;
class AProjectileBase;
class UHealthComponent;

UCLASS()
class TOONTANKS_API APawnBase : public APawn
{
    GENERATED_BODY()

public:
    // Sets default values for this pawn's properties
    APawnBase();

    virtual void HandleDestruction();

protected:
    virtual void RotateTurret(const FVector Target);

    virtual void Fire();

private:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta= (AllowPrivateAccess="true"))
    UCapsuleComponent* CapsuleComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta= (AllowPrivateAccess="true"))
    UStaticMeshComponent* BaseMesh;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta= (AllowPrivateAccess="true"))
    UStaticMeshComponent* TurretMesh;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta= (AllowPrivateAccess="true"))
    USceneComponent* ProjectileSpawnPoint;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Combat", meta= (AllowPrivateAccess="true"))
    TSubclassOf<AProjectileBase> ProjectileClass;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta= (AllowPrivateAccess="true"))
    UHealthComponent* HealthComponent;

    UPROPERTY(EditAnywhere, Category="Combat|Effects", meta= (AllowPrivateAccess="true"))
    UParticleSystem* DeathParticle;
};
