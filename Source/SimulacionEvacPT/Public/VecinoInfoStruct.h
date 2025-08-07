#pragma once

#include "CoreMinimal.h"
#include "VecinoInfoStruct.generated.h"

USTRUCT(BlueprintType)
struct SIMULACIONEVACPT_API FVecinoInfo
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Vecino")
    AActor* InterseccionDestino = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Vecino")
    AActor* CaminoSpline = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Vecino")
    float Costo = 0.f;
};
