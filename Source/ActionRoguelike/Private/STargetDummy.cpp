// Fill out your copyright notice in the Description page of Project Settings.


#include "STargetDummy.h"

#include "SAttributeComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ASTargetDummy::ASTargetDummy()
{

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("MeshComp");
	RootComponent = MeshComp;

	AttributeComp = CreateDefaultSubobject<USAttributeComponent>("AttributeComp");

	AttributeComp->OnHealthChanged.AddDynamic(this, &ASTargetDummy::OnHealthChanged);

}

void ASTargetDummy::OnHealthChanged(AActor* InstigatorActor, USAttributeComponent* OwningComp, float NewHealth, float Delta)
{
a	if (Delta < 0.0f)
	{
		MeshComp->SetScalarParameterValueOnMaterials("TimeToHit", GetWorld()->TimeSeconds);
	}
}