// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "ProjectileBase.generated.h"

class UProjectileMovementComponent;

UCLASS()
class TOONTANKS_API AProjectileBase : public AActor
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    AProjectileBase();

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

private:

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta=(AllowPrivateAccess = "true"))
    UProjectileMovementComponent* ProjectileMovement;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta=(AllowPrivateAccess = "true"))
    UStaticMeshComponent* ProjectileMesh;

    UPROPERTY(EditDefaultsOnly, Category="Damage")
    TSubclassOf<UDamageType> DamageType;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Movement", meta=(AllowPrivateAccess = "true"))
    float MovementSpeed = 1500;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Damage", meta=(AllowPrivateAccess = "true"))
    float Damage = 50;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Movement", meta=(AllowPrivateAccess = "true"))
    float LifeTime = 3;

    UFUNCTION(BlueprintCallable, meta=(BlueprintProtected = "true"), Category="Game")
    void OnHit(UPrimitiveComponent* HitComponent,
               AActor* OtherActor, UPrimitiveComponent* OtherComp,
               FVector NormalImpulse,
               const FHitResult& Hit);
};
