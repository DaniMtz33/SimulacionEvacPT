#include "PathfindingLibrary.h"
#include "UObject/UnrealType.h"
#include "Kismet/GameplayStatics.h"
#include "Containers/Queue.h"
#include "VecinoInfoStruct.h"

TArray<AActor*> UPathfindingLibrary::FindPathToZonaSegura(AActor* NodoInicial)
{
	TArray<AActor*> Camino;
	if (!NodoInicial) return Camino;

	// Buscar zonas seguras en el mapa
	TArray<AActor*> TodosLosActores;
	UGameplayStatics::GetAllActorsOfClass(NodoInicial->GetWorld(), AActor::StaticClass(), TodosLosActores);

	TArray<AActor*> ZonasSeguras;

	for (AActor* Actor : TodosLosActores)
	{
		if (Actor && Actor->GetClass()->GetName().Contains(TEXT("BP_Interseccion")))
		{
			FBoolProperty* ZonaProp = FindFProperty<FBoolProperty>(Actor->GetClass(), TEXT("bEsZonaSegura"));
			if (ZonaProp && ZonaProp->GetPropertyValue_InContainer(Actor))
			{
				ZonasSeguras.Add(Actor);
			}
		}
	}

	if (ZonasSeguras.Num() == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("No se encontraron zonas seguras en el mapa"));
		return Camino;
	}

	// Estructuras A*
	TArray<AActor*> OpenSet;
	TMap<AActor*, float> GScore; // Costo real acumulado
	TMap<AActor*, float> FScore; // G + heurística
	TMap<AActor*, AActor*> CameFrom;

	OpenSet.Add(NodoInicial);
	GScore.Add(NodoInicial, 0.f);
	FScore.Add(NodoInicial, 0.f);

	while (OpenSet.Num() > 0)
	{
		// Elegir nodo con menor FScore
		AActor* Actual = OpenSet[0];
		float MejorF = FScore.Contains(Actual) ? FScore[Actual] : FLT_MAX;

		for (AActor* Nodo : OpenSet)
		{
			float Score = FScore.Contains(Nodo) ? FScore[Nodo] : FLT_MAX;
			if (Score < MejorF)
			{
				Actual = Nodo;
				MejorF = Score;
			}
		}

		OpenSet.Remove(Actual);

		// ¿Es zona segura?
		FBoolProperty* ZonaProp = FindFProperty<FBoolProperty>(Actual->GetClass(), TEXT("bEsZonaSegura"));
		bool bEsZonaSegura = ZonaProp ? ZonaProp->GetPropertyValue_InContainer(Actual) : false;

		if (bEsZonaSegura)
		{
			// Reconstruir camino
			AActor* Nodo = Actual;
			while (CameFrom.Contains(Nodo))
			{
				Camino.Insert(Nodo, 0);
				Nodo = CameFrom[Nodo];
			}
			Camino.Insert(NodoInicial, 0);
			return Camino;
		}

		// Leer vecinos
		FArrayProperty* VecinosProp = FindFProperty<FArrayProperty>(Actual->GetClass(), TEXT("Vecinos"));
		if (!VecinosProp) continue;

		FScriptArrayHelper VecinosArrayHelper(VecinosProp, VecinosProp->ContainerPtrToValuePtr<void>(Actual));
		UE_LOG(LogTemp, Warning, TEXT("Intersección: %s tiene %d vecinos"),
			*Actual->GetName(), VecinosArrayHelper.Num());

		for (int32 i = 0; i < VecinosArrayHelper.Num(); ++i)
		{
			uint8* VecinoStruct = VecinosArrayHelper.GetRawPtr(i);
			if (!VecinoStruct) continue;

			FObjectProperty* DestProp = FindFProperty<FObjectProperty>(VecinosProp->Inner->GetOwnerStruct(), TEXT("InterseccionDestino"));
			FFloatProperty* CostoProp = FindFProperty<FFloatProperty>(VecinosProp->Inner->GetOwnerStruct(), TEXT("Costo"));

			AActor* Destino = DestProp ? Cast<AActor>(DestProp->GetObjectPropertyValue_InContainer(VecinoStruct)) : nullptr;
			float Costo = CostoProp ? CostoProp->GetPropertyValue_InContainer(VecinoStruct) : 0.f;

			if (!Destino)
			{
				UE_LOG(LogTemp, Error, TEXT(" → Vecino sin destino válido (nullptr) en %s"), *Actual->GetName());
				continue;
			}

			UE_LOG(LogTemp, Warning, TEXT(" → Vecino: %s | Costo: %.2f"), *Destino->GetName(), Costo);

			// gScore = Costo real acumulado
			float NuevoGScore = GScore.Contains(Actual) ? GScore[Actual] + Costo : Costo;

			if (!GScore.Contains(Destino) || NuevoGScore < GScore[Destino])
			{
				CameFrom.Add(Destino, Actual);
				GScore.Add(Destino, NuevoGScore);

				// Heurística: distancia a la zona segura más cercana
				float DistMin = FLT_MAX;
				for (AActor* Zona : ZonasSeguras)
				{
					float Dist = FVector::Dist(Destino->GetActorLocation(), Zona->GetActorLocation());
					if (Dist < DistMin)
					{
						DistMin = Dist;
					}
				}
				float Heuristica = DistMin;
				FScore.Add(Destino, NuevoGScore + Heuristica);

				if (!OpenSet.Contains(Destino))
				{
					OpenSet.Add(Destino);
				}
			}
		}
	}

	// No se encontró ruta
	return Camino;
}
