// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/LandDecal.h"
#include "Engine/DecalActor.h"
#include "Components/DecalComponent.h"
#include "Engine/DamageEvents.h"
#include "Kismet/GameplayStatics.h"
#include "../Player/MyPlayer.h"


void ALandDecal::DeActiveEvent(FVector location)
{
    TArray<AActor*> foundPlayers;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), AMyPlayer::StaticClass(), foundPlayers);

    for (AActor* actor : foundPlayers)
    {
        AMyPlayer* player = Cast<AMyPlayer>(actor);
        if (player)
        {
            float distance = FVector::Dist(player->GetActorLocation(), location);

            if (distance <= 600)
            {
                UGameplayStatics::ApplyDamage(player, 50.f, GetInstigatorController(), this, UDamageType::StaticClass());
            }
        }
    } 
}
