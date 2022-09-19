// Fill out your copyright notice in the Description page of Project Settings.


#include "SPickupBase.h"

#include "Components/StaticMeshComponent.h"
#include "TimerManager.h"
#include "Net/UnrealNetwork.h"

// Sets default values
ASPickupBase::ASPickupBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("MeshComp");
	RootComponent = MeshComp;

	RespawnTime = 10.0f;

	SetReplicates(true);

	bIsActive = true;
}

void ASPickupBase::TriggerPickupTimer()
{
	FTimerDelegate Delegate = FTimerDelegate::CreateUObject(this, &ASPickupBase::Respawn);
	GetWorldTimerManager().SetTimer(TimerHandle_Respawn, Delegate, RespawnTime, false);

	SetIsActive(false);
}

void ASPickupBase::Respawn()
{
	SetIsActive(true);
}

void ASPickupBase::SetIsActive(bool IsActive)
{
	MeshComp->SetCollisionEnabled(IsActive ? ECollisionEnabled::QueryOnly : ECollisionEnabled::NoCollision);
	MeshComp->SetVisibility(IsActive);
	bIsActive = IsActive;
}

void ASPickupBase::OnRep_IsActive()
{
	SetIsActive(bIsActive);
}

void ASPickupBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ASPickupBase, bIsActive);
}