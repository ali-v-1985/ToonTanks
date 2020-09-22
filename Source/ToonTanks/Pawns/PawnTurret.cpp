// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnTurret.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "PawnTank.h"
#include "TimerManager.h"

APawnTurret::APawnTurret()
{
    
}

void APawnTurret::BeginPlay()
{
    Super::BeginPlay();

    PlayerPawn = Cast<APawnTank>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
    
    GetWorld()->GetTimerManager().SetTimer(FireRateTimerHandle, this,
                                           &APawnTurret::FireIfPossible,
                                           FireRate,
                                           true);
}

void APawnTurret::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    RotateTurretIfEnemyInRange();   
}

void APawnTurret::HandleDestruction()
{
    Super::HandleDestruction();
    Destroy();
}

void APawnTurret::FireIfPossible()
{
    if(!PlayerPawn || GetPlayerDistance() > FireRange) return;

    Fire();
}

void APawnTurret::RotateTurretIfEnemyInRange()
{
    if(!PlayerPawn || GetPlayerDistance() > FireRange) return;

    RotateTurret(PlayerPawn->GetActorLocation());
}

float APawnTurret::GetPlayerDistance() const
{
    if(!PlayerPawn) return 0.0f;

    return  FVector::Dist(GetActorLocation(),PlayerPawn->GetActorLocation());
}
