// Fill out your copyright notice in the Description page of Project Settings.


#include "InterseccionBase.h"
#include "Components/BoxComponent.h"

AInterseccionBase::AInterseccionBase()
{
	PrimaryActorTick.bCanEverTick = false;

	// Crear raíz
	USceneComponent* SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
	RootComponent = SceneRoot;

	// Crear sensor tipo box
	SensorDeLlegada = CreateDefaultSubobject<UBoxComponent>(TEXT("SensorDeLlegada"));
	SensorDeLlegada->SetupAttachment(RootComponent);
	SensorDeLlegada->SetBoxExtent(FVector(100.0f)); // Cambia el tamaño si es necesario
	SensorDeLlegada->SetCollisionProfileName(TEXT("OverlapAll")); // Ajusta si tienes uno personalizado
}

void AInterseccionBase::BeginPlay()
{
	Super::BeginPlay();
}