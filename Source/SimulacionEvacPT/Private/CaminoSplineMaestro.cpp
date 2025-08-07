#include "CaminoSplineMaestro.h"
#include "Components/SplineComponent.h"

ACaminoSplineMaestro::ACaminoSplineMaestro()
{
	PrimaryActorTick.bCanEverTick = false;

	// Componente raíz
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));

	// Crear spline
	SplineMaestro = CreateDefaultSubobject<USplineComponent>(TEXT("SplineMaestro"));
	SplineMaestro->SetupAttachment(RootComponent);
}

void ACaminoSplineMaestro::BeginPlay()
{
	Super::BeginPlay();
}

USplineComponent* ACaminoSplineMaestro::ObtenerComponenteSpline() const
{
	return SplineMaestro;
}
