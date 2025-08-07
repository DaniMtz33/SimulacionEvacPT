// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "VecinoInfoStruct.h" // Aseg�rate que est� bien incluido
#include "CaminoSplineMaestro.h"
#include "Components/BoxComponent.h"
#include "InterseccionBase.generated.h"

UCLASS()
class SIMULACIONEVACPT_API AInterseccionBase : public AActor
{
	GENERATED_BODY()

public:
	AInterseccionBase();

protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Componentes")
	UBoxComponent* SensorDeLlegada;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Intersecci�n")
	TArray<class ACaminoSplineMaestro*> SplinesDeSalida;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Intersecci�n")
	bool bEsZonaSegura = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Intersecci�n")
	TArray<FVecinoInfo> Vecinos_Old;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Intersecci�n")
	AActor* ProximaInterseccion;
};
