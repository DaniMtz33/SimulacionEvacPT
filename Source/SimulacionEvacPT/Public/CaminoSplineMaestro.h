// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CaminoSplineMaestro.generated.h"

UCLASS()
class SIMULACIONEVACPT_API ACaminoSplineMaestro : public AActor
{
	GENERATED_BODY()

public:
	ACaminoSplineMaestro();

protected:
	virtual void BeginPlay() override;

public:
	// Componente spline
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spline")
	class USplineComponent* SplineMaestro;

	// Variables
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spline")
	float Longitud;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Intersecciones")
	AActor* InterseccionDelInicio;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Intersecciones")
	AActor* InterseccionDeLlegada;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Spline")
	class USplineComponent* ObtenerComponenteSpline() const;
};
