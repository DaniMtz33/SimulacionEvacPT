#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "VecinoInfoStruct.h" // <-- Tu struct
#include "VecinoTestLibrary.generated.h"

UCLASS()
class SIMULACIONEVACPT_API UVecinoTestLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

public:

    // Devuelve un array de prueba con datos simulados
    UFUNCTION(BlueprintCallable, Category = "Pruebas|Vecino")
    static TArray<FVecinoInfo> ObtenerVecinosDePrueba();
};
