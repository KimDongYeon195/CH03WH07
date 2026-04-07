// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MyPlayerController.generated.h"

class UInputAction;
class UInputMappingContext;

UCLASS()
class CH03HW07_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AMyPlayerController();

	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = "IA|Input")
	UInputMappingContext* IMC;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "IA|Input");
	UInputAction* IAMove;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "IA|Input");
	UInputAction* IALook;

protected:
	virtual void BeginPlay() override;
	
};
