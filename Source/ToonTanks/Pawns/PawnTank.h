// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PawnBase.h"
#include "PawnTank.generated.h"

class UCameraComponent;
class USpringArmComponent;
/**
 * 
 */
UCLASS()
class TOONTANKS_API APawnTank : public APawnBase
{
    GENERATED_BODY()

public:
    APawnTank();

    // Called every frame
    virtual void Tick(float DeltaTime) override;

    // Called to bind functionality to input
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    virtual void HandleDestruction() override;

    bool GetIsPlayerAlive() const;
protected:
    virtual void Fire() override;
    
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

private:

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Camera", meta = (AllowPrivateAccess="true"))
    USpringArmComponent* SpringArmComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Camera", meta = (AllowPrivateAccess="true"))
    UCameraComponent* CameraComponent;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Movement", meta = (AllowPrivateAccess="true"))
    float MoveSpeed = 100.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Movement", meta = (AllowPrivateAccess="true"))
    float RotateSpeed = 100.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Combat", meta = (AllowPrivateAccess="true"))
    float LoadTime = 1;
    
    float LastFireTime;

    FVector MoveDirection;
    FQuat RotationDirection;

    APlayerController* PlayerControllerRef;

    bool bIsPlayerAlive;

    void CalculateMoveInput(float Value);
    void CalculateRotateInput(float Value);

    void Move();
    void Rotate();
    void LookTowardCursor();
    bool IsLoaded() const;
};
