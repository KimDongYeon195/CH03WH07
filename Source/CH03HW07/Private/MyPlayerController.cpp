// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerController.h"
#include "EnhancedInputSubsystems.h"

AMyPlayerController::AMyPlayerController():
	IMC(nullptr),
	IAMove(nullptr),
	IALook(nullptr)
{
}

void AMyPlayerController::BeginPlay()
{
	Super::BeginPlay();
	if (ULocalPlayer* LocalPlayer = GetLocalPlayer()) //로컬 플레이어의 입력이나 화면을 관리하는 객체
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>()) 
		{
			if (IMC)
			{
				Subsystem->AddMappingContext(IMC, 0);//인덱스 0번 -> 최우선순위
			}
		}
	}
}
