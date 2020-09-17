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
}

void APawnTurret::FireIfPossible()
{
    if(!PlayerPawn) return;

    if(GetPlayerDistance() <= FireRange)
        UE_LOG(LogTemp, Display, TEXT("In the Fire Range"));
}

float APawnTurret::GetPlayerDistance()
{
    if(!PlayerPawn) return 0.0f;

    return  FVector::Dist(GetActorLocation(),PlayerPawn->GetActorLocation());
}
