#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "SplineSaveLibrary.generated.h"

// Forward Declarations
class USplineComponent;
class ACaminoSplineMaestro;
class AInterseccionBase;

// ----- Estructura que representa un punto del spline -----
USTRUCT()
struct FSplinePointData
{
	GENERATED_BODY()

	UPROPERTY()
	FVector LocalPosition;

	UPROPERTY()
	FVector ArriveTangent;

	UPROPERTY()
	FVector LeaveTangent;

	// Necesario para poder guardar/cargar este struct
	friend FArchive& operator<<(FArchive& Ar, FSplinePointData& Punto)
	{
		Ar << Punto.LocalPosition;
		Ar << Punto.ArriveTangent;
		Ar << Punto.LeaveTangent;
		return Ar;
	}
};

// ----- Estructura completa para guardar un spline -----
USTRUCT()
struct FCaminoSplineData
{
	GENERATED_BODY()

	UPROPERTY()
	FName NombreActor;

	UPROPERTY()
	TArray<FSplinePointData> Puntos;

	UPROPERTY()
	FName NombreInterseccionInicio;

	UPROPERTY()
	FName NombreInterseccionLlegada;

	// Necesario para poder guardar/cargar este struct
	friend FArchive& operator<<(FArchive& Ar, FCaminoSplineData& Data)
	{
		Ar << Data.NombreActor;
		Ar << Data.Puntos;
		Ar << Data.NombreInterseccionInicio;
		Ar << Data.NombreInterseccionLlegada;
		return Ar;
	}
};

// ----- Clase para guardar y cargar datos -----
UCLASS()
class SIMULACIONEVACPT_API USplineSaveLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	// Guarda todos los BP_CaminoSpline_Maestro en archivo binario
	UFUNCTION(BlueprintCallable, Category = "Spline Save", meta = (WorldContext = "WorldContext"))
	static void GuardarTodosLosSplines(UObject* WorldContext, const FString& RutaArchivo);

	//
};// Restaura todos los BP_CaminoSpline_Maestro desde archivo binario
	//UFUNCTION(BlueprintCallable, Category = "Spline Save", meta = (WorldContext = "WorldContext"))
	//static void RestaurarTodosLosSplines(UObject* WorldContext, const FString& RutaArchivo);
