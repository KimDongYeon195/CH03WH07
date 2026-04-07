// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MyPawn.generated.h"

class UCapsuleComponent;
class USpringArmComponent;
class UCameraComponent;
struct FInputActionValue;

UCLASS()
class CH03HW07_API AMyPawn : public APawn
{
	GENERATED_BODY()

public:
	AMyPawn();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MyPawn|Collision")
	UCapsuleComponent* CapsuleComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MyPawn|Collision")
	USkeletalMeshComponent* SkeletalMeshComp;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MyPawn|Camera")
	USpringArmComponent* SpringArmComp;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MyPawn|Camera")
	UCameraComponent* CameraComp;

protected:
	virtual void BeginPlay() override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
	void Move(const FInputActionValue& value); //IA의 valuetype을 반환(현재 Axis2D)
	UFUNCTION()								   //구조체, 클래스등은 크기가 커서 참조로 가져옴
	void Look(const FInputActionValue& value);

public:	
	virtual void Tick(float DeltaTime) override;


};

//CapsuleComponent
//SkeletalMeshCompnnent
//SpringArmComponent
//CameraComponent