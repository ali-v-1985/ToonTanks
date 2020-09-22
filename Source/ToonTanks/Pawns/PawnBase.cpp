// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnBase.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "ToonTanks/Actors/ProjectileBase.h"
#include "ToonTanks/Components/HealthComponent.h"

// Sets default values
APawnBase::APawnBase()
{
    // Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider"));
    RootComponent = CapsuleComponent;

    BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
    BaseMesh->SetupAttachment(CapsuleComponent);

    TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Mesh"));
    TurretMesh->SetupAttachment(BaseMesh);

    ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile Spawn Point"));
    ProjectileSpawnPoint->SetupAttachment(TurretMesh);

    HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Health"));
}

void APawnBase::RotateTurret(const FVector Target)
{
    const auto TurretLocation = TurretMesh->GetComponentLocation();
    const auto LookAtTarget = FVector(Target.X, Target.Y, TurretLocation.Z);
    const auto Rotation = (LookAtTarget - TurretLocation).Rotation();
    TurretMesh->SetWorldRotation(Rotation, true);
}

void APawnBase::Fire()
{
    if (ProjectileClass)
    {
        const auto SpawnLocation = ProjectileSpawnPoint->GetComponentLocation();
        const auto SpawnRotation = ProjectileSpawnPoint->GetComponentRotation();
        auto ProjectileObj = GetWorld()->SpawnActor<AProjectileBase>(ProjectileClass,
                                                                      SpawnLocation, SpawnRotation);
        ProjectileObj->SetOwner(this);
    }
}

void APawnBase::HandleDestruction()
{
    UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), DeathParticle, GetActorLocation());
}
