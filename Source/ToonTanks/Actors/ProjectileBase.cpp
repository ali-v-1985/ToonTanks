// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileBase.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"

AProjectileBase::AProjectileBase()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = false;

    ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Mesh"));
    RootComponent = ProjectileMesh;

    ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement"));
    ProjectileMovement->InitialSpeed = MovementSpeed;
    ProjectileMovement->MaxSpeed = MovementSpeed;
    InitialLifeSpan = LifeTime;
}

// Sets default values

// Called when the game starts or when spawned
void AProjectileBase::BeginPlay()
{
    Super::BeginPlay();

    ProjectileMesh->OnComponentHit.AddDynamic(this, &AProjectileBase::OnHit);
}

void AProjectileBase::OnHit(UPrimitiveComponent* HitComponent,
                            AActor* OtherActor, UPrimitiveComponent* OtherComp,
                            FVector NormalImpulse,
                            const FHitResult& Hit)
{
    const auto OwnerActor = GetOwner();
    if (!OwnerActor) return;
    if (OtherActor && OtherActor != this && OtherActor != OwnerActor)
    {
        const auto PlayerController = OwnerActor->GetInstigatorController();
        UGameplayStatics::ApplyDamage(OtherActor, Damage, PlayerController,
                                                           this, DamageType);

        UGameplayStatics::SpawnEmitterAtLocation(this, HitParticle, GetActorLocation());
        Destroy();
    }
}
