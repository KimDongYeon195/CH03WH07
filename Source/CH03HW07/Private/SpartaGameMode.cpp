// Fill out your copyright notice in the Description page of Project Settings.


#include "SpartaGameMode.h"
#include "MyPawn.h"

ASpartaGameMode::ASpartaGameMode()
{
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GameMode");
	DefaultPawnClass = AMyPawn::StaticClass();
}