#include "VecinoTestLibrary.h"
#include "GameFramework/Actor.h"

TArray<FVecinoInfo> UVecinoTestLibrary::ObtenerVecinosDePrueba()
{
    TArray<FVecinoInfo> Vecinos;

    FVecinoInfo Vecino1;
    Vecino1.InterseccionDestino = nullptr; // No ponemos Actor real, es solo para probar visibilidad
    Vecino1.CaminoSpline = nullptr;
    Vecino1.Costo = 10.f;

    FVecinoInfo Vecino2;
    Vecino2.InterseccionDestino = nullptr;
    Vecino2.CaminoSpline = nullptr;
    Vecino2.Costo = 15.f;

    Vecinos.Add(Vecino1);
    Vecinos.Add(Vecino2);

    return Vecinos;
}
