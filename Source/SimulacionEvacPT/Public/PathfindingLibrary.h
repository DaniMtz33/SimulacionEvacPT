#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "PathfindingLibrary.generated.h"

UCLASS()
class SIMULACIONEVACPT_API UPathfindingLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	// Esta función devuelve el camino desde una intersección a una zona segura
	UFUNCTION(BlueprintCallable, Category = "Evacuacion|Pathfinding")
	static TArray<AActor*> FindPathToZonaSegura(AActor* InterseccionInicio);
};