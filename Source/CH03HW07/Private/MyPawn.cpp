// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPawn.h"


AMyPawn::AMyPawn()
{
 	
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	SetRootComponent(CapsuleComp);

	SkeletalMeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
	SkeletalMeshComp->SetupAttachment(CapsuleComp);
}

void AMyPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

void AMyPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMyPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

