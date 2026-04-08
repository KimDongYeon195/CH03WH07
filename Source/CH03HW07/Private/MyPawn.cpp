// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPawn.h"
#include "Components/CapsuleComponent.h" //캡슐컴포넌트 헤더 추가
#include "Camera/CameraComponent.h"//카메라컴포넌트 헤더 추가
#include "GameFramework/SpringArmComponent.h" //스프링암컴포넌트 헤더 추가
#include "GameFramework/FloatingPawnMovement.h" //폰 클래스에 행동 제어(?)기능 추가
#include "EnhancedInputComponent.h"
#include "MyPlayerController.h"
AMyPawn::AMyPawn()
{
 	
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
	SetRootComponent(CapsuleComp);
	CapsuleComp->SetSimulatePhysics(false);

	SkeletalMeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
	SkeletalMeshComp->SetupAttachment(CapsuleComp);
	SkeletalMeshComp->SetSimulatePhysics(false);

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArmComp ->SetupAttachment(CapsuleComp);
	SpringArmComp->TargetArmLength = 300.0f;
	SpringArmComp->bUsePawnControlRotation = true;

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComp->SetupAttachment(SpringArmComp, USpringArmComponent::SocketName);
	CameraComp->bUsePawnControlRotation = false;

	MovementComp = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("MovementComp"));

	MoveSpeed = 400.f;
	RotationSpeed = 100.f;
}


void AMyPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		if (AMyPlayerController* PlayerController = Cast<AMyPlayerController>(GetController()))
		{
			if (PlayerController->IAMove)
			{
				EnhancedInput->BindAction(PlayerController->IAMove, ETriggerEvent::Triggered,
					this, &AMyPawn::Move);
			}
			if (PlayerController->IALook)
			{
				EnhancedInput->BindAction(PlayerController->IALook, ETriggerEvent::Triggered,
					this, &AMyPawn::Look);
			}
		}
	}

}

void AMyPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


}

void AMyPawn::Move(const FInputActionValue& value)
{	 
	if (!Controller) return;

	const FVector2D MoveInput = value.Get<FVector2D>();
	float DeltaTime = GetWorld()->GetDeltaSeconds();

	FVector DeltaMove = FVector(MoveInput.X, MoveInput.Y, 0.0f);
	DeltaMove = DeltaMove * MoveSpeed * DeltaTime;

	AddActorLocalOffset(DeltaMove, true);


}	 


void AMyPawn::Look(const FInputActionValue& value) //value : FinputActionValue(EnhancedInputSystem)의 마우스  X,Y축 이동 데이터
{
	FVector2D LookInput = value.Get<FVector2D>(); //value의 2차원 벡터를 가져옴 = Lookinput
	float DeltaTime = GetWorld()->GetDeltaSeconds();
	
	float DeltaYaw = LookInput.X * RotationSpeed * DeltaTime; //LookInput의 X축 이동(Yaw) * 회전속도 * 1프레임 실행 속도
	float DeltaPitch = LookInput.Y * RotationSpeed * DeltaTime; //LookInput의 Y축 이동(Pitch) * 회전속도 * 1프레임 실행 속도
	AddActorLocalRotation(FRotator(0.0f, DeltaYaw, 0.0f)); //FRotator(Pitch, Yaw, Roll) // 폰의 Yaw

	if (AController* PlayerControllerPtr = GetController()) //AController -> pawn제어 주체(현재: SpringArm)의 포인터
	{
		FRotator CurrentRot = PlayerControllerPtr->GetControlRotation();
			//회전값 CurrentRot에 현재컨트롤러의 회전값 가져옴 -> FRotator(0.0f, DeltaYaw, 0.0f)

		float SpringArmPitch = CurrentRot.Pitch + (DeltaPitch * -1.0f); 
			//현재회전값의 Pitch에 DeltqPitch값 더함. -1.f 곱하는 이유는 상하 반전

		PlayerControllerPtr->SetControlRotation(FRotator(SpringArmPitch, GetActorRotation().Yaw, 0.0f));
			//최종 컨트롤러의 회전값
	}
	//AddControllerYawInput(LookInput.X);
	//AddControllerPitchInput(LookInput.Y);
}