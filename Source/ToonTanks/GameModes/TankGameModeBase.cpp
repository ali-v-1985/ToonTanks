// Fill out your copyright notice in the Description page of Project Settings.


#include "TankGameModeBase.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "ToonTanks/Pawns/PawnTurret.h"

void ATankGameModeBase::BeginPlay()
{
    Super::BeginPlay();
    HandleGameStart();
}

void ATankGameModeBase::ActorDied(AActor* DeadActor)
{
    if(DeadActor == PlayerTank)
    {
        PlayerTank->HandleDestruction();
        HandleGameOver(false);
    }
    else if(APawnTurret* DestroyedTurret = Cast<APawnTurret>(DeadActor))
    {
        DestroyedTurret->HandleDestruction();
        if(--TurretCount == 0)
        {
            HandleGameOver(true);
        }
    }
}

void ATankGameModeBase::HandleGameStart()
{
    LoadTurretActorsCount();

    PlayerTank = Cast<APawnTank>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
    
    GameStart();
}

void ATankGameModeBase::HandleGameOver(bool PlayerWon)
{
    GameOver(PlayerWon);
}

void ATankGameModeBase::LoadTurretActorsCount()
{
    TArray<AActor*> TurretActors;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), APawnTurret::StaticClass(), TurretActors);
    TurretCount = TurretActors.Num();
}

