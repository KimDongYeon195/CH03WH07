// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MyPawn.generated.h"

class UCapsuleComponent;
class USpringArmComponent;
class UCameraComponent;
class UFloatingPawnMovement;
struct FInputActionValue;

UCLASS()
class CH03HW07_API AMyPawn : public APawn
{
	GENERATED_BODY()

public:
	AMyPawn();


protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MyPawn|Collision")
	UCapsuleComponent* CapsuleComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MyPawn|Collision")
	USkeletalMeshComponent* SkeletalMeshComp;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MyPawn|Camera")
	USpringArmComponent* SpringArmComp;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MyPawn|Camera")
	UCameraComponent* CameraComp;

	UPROPERTY(VisibleAnywhere, Category = "Movement")
	UFloatingPawnMovement* MovementComp;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()								   
	void Look(const FInputActionValue& value);

	UFUNCTION()
	void Move(const FInputActionValue& value); //입력바인딩 함수
											   //IA의 valuetype을 반환(현재 Axis2D)
	UPROPERTY(VisibleAnywhere,BluePrintReadWrite, Category = "Movement")
	float MoveSpeed;
	UPROPERTY(VisibleAnywhere, BluePrintReadWrite, Category = "Movement")
	float RotationSpeed;
public:	
	virtual void Tick(float DeltaTime) override;


};

//CapsuleComponent
//SkeletalMeshCompnnent
//SpringArmComponent
//CameraComponent