#include "SplineSaveLibrary.h"
#include "Components/SplineComponent.h"
#include "EngineUtils.h"
#include "Misc/FileHelper.h"
#include "Serialization/BufferArchive.h"
#include "Serialization/MemoryWriter.h"

void USplineSaveLibrary::GuardarTodosLosSplines(UObject* WorldContext, const FString& RutaArchivo)
{
	if (!WorldContext) return;

	// Array para guardar todos los datos de spline
	TArray<FCaminoSplineData> DatosASalvar;

	// Iteramos sobre TODOS los actores en el mundo
	for (TActorIterator<AActor> It(WorldContext->GetWorld()); It; ++It)
	{
		AActor* Actor = *It;

		// Solo tomamos los que sean del tipo Blueprint "BP_CaminoSpline_Maestro"
		if (!Actor || !Actor->GetClass()->GetName().Contains(TEXT("BP_CaminoSpline_Maestro")))
			continue;

		// Intentamos obtener el componente spline
		USplineComponent* Spline = Actor->FindComponentByClass<USplineComponent>();
		if (!Spline) continue;

		// Creamos la estructura con la info que queremos respaldar
		FCaminoSplineData Data;
		Data.NombreActor = Actor->GetFName();

		// NOTA: No puedes guardar aún referencias de intersección sin reparentar.
		// Se puede ampliar si hay variables accesibles desde Blueprint por nombre

		// Guardamos los puntos del spline
		const int32 NumPuntos = Spline->GetNumberOfSplinePoints();
		for (int32 i = 0; i < NumPuntos; ++i)
		{
			FSplinePointData Punto;
			Punto.LocalPosition = Spline->GetLocationAtSplinePoint(i, ESplineCoordinateSpace::Local);
			Punto.ArriveTangent = Spline->GetArriveTangentAtSplinePoint(i, ESplineCoordinateSpace::Local);
			Punto.LeaveTangent = Spline->GetLeaveTangentAtSplinePoint(i, ESplineCoordinateSpace::Local);
			Data.Puntos.Add(Punto);
		}

		DatosASalvar.Add(Data);
	}

	// Guardamos en binario
	FBufferArchive Archivo;
	Archivo << DatosASalvar;

	if (FFileHelper::SaveArrayToFile(Archivo, *RutaArchivo))
	{
		UE_LOG(LogTemp, Warning, TEXT("✔ Se guardaron %d splines en %s"), DatosASalvar.Num(), *RutaArchivo);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("✖ No se pudo guardar el archivo en %s"), *RutaArchivo);
	}

	Archivo.FlushCache();
	Archivo.Empty();
}
