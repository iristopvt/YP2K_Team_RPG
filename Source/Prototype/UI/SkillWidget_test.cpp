#include "SkillWidget_test.h"
#include "Components/Image.h"
#include "../Player/MyPlayer.h"
#include "TimerManager.h"

void USkillWidget_test::NativeConstruct()
{
    SkillImages.Add(SkillImage1);
    SkillImages.Add(SkillImage2);
    SkillImages.Add(SkillImage3);
    SkillImages.Add(SkillImage4);

    CooldownOverlays.Add(Cooldown1);
    CooldownOverlays.Add(Cooldown2);
    CooldownOverlays.Add(Cooldown3);
    CooldownOverlays.Add(Cooldown4);

    CooldownTimes.Init(0.0f, 4);
    MaxCooldownTimes.Init(0.0f, 4);
    CooldownTimerHandles.Init(FTimerHandle(), 4);

    SkillLocked.Init(false, 4);

    for (UImage *cd : CooldownOverlays)
    {
        if (cd)
        {
            cd->SetOpacity(0.0f);
        }
    }
}



void USkillWidget_test::StartCooldown(int32 SkillIndex, float InMaxCooldownTime)
{
    if (SkillIndex < 0 || SkillIndex >= CooldownOverlays.Num()|| SkillLocked[SkillIndex])
        return;

    MaxCooldownTimes[SkillIndex] = InMaxCooldownTime;
    CooldownTimes[SkillIndex] = MaxCooldownTimes[SkillIndex];

    if (CooldownOverlays[SkillIndex])
    {
        CooldownOverlays[SkillIndex]->SetOpacity(0.5f);
    }

    GetWorld()->GetTimerManager().SetTimer(CooldownTimerHandles[SkillIndex], [this, SkillIndex]()
                                           {
    float DeltaTime = GetWorld()->GetDeltaSeconds(); 
    CooldownTimes[SkillIndex] -= DeltaTime;

    UpdateCooldown(SkillIndex);

    if (CooldownTimes[SkillIndex] <= 0.0f)
    {
        CooldownTimes[SkillIndex] = 0.0f;
        GetWorld()->GetTimerManager().ClearTimer(CooldownTimerHandles[SkillIndex]);

        if (CooldownOverlays[SkillIndex])
        {
            CooldownOverlays[SkillIndex]->SetOpacity(0.0f);
        }

        AMyPlayer* Player = Cast<AMyPlayer>(GetWorld()->GetFirstPlayerController()->GetPawn());
        if (Player)
        {
            Player->SetSkillOnCooldown(SkillIndex, false);
        }
    } }, GetWorld()->GetDeltaSeconds(), true); 
}

void USkillWidget_test::ClearAll()
{
     for (int32 i = 0; i < CooldownTimerHandles.Num(); ++i)
    {
        if (GetWorld() && GetWorld()->GetTimerManager().IsTimerActive(CooldownTimerHandles[i]))
        {
            GetWorld()->GetTimerManager().ClearTimer(CooldownTimerHandles[i]);
        }
    }
}

void USkillWidget_test::LockAllSkill()
{
    for (int32 i = 0; i < SkillLocked.Num(); ++i)
    {
        SkillLocked[i] = true;

        if (CooldownOverlays.IsValidIndex(i) && CooldownOverlays[i])
        {
            CooldownOverlays[i]->SetOpacity(0.8f);
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("CooldownOverlay[%d] is invalid!"), i);
        }
    }

}

void USkillWidget_test::UnLockAllSkill()
{
    for (int32 i = 0; i < SkillLocked.Num(); ++i)
    {
        SkillLocked[i] = false;

        if (CooldownOverlays[i])
        {
            CooldownOverlays[i]->SetOpacity(0.0f);
        }
    }
}

bool USkillWidget_test::IsSkillLocked(int32 index)
{
    if (SkillLocked.IsValidIndex(index))
    {
        return SkillLocked[index];
    }
    return true;
}

void USkillWidget_test::UpdateCooldown(int32 SkillIndex)
{
    if (SkillIndex < 0 || SkillIndex >= CooldownTimes.Num())
        return;

    CooldownTimes[SkillIndex] -= GetWorld()->DeltaTimeSeconds;

    if (CooldownTimes[SkillIndex] <= 0.0f)
    {
        GetWorld()->GetTimerManager().ClearTimer(CooldownTimerHandles[SkillIndex]);

        if (CooldownOverlays[SkillIndex])
        {
            FSlateBrush Brush = CooldownOverlays[SkillIndex]->GetBrush();
            Brush.ImageSize = FVector2D(Brush.ImageSize.X, SkillImage1->GetDesiredSize().Y);
            CooldownOverlays[SkillIndex]->SetBrush(Brush);

            CooldownOverlays[SkillIndex]->SetOpacity(0.0f);
        }
    }
    else
    {
        float Percent = CooldownTimes[SkillIndex] / MaxCooldownTimes[SkillIndex];

        if (CooldownOverlays[SkillIndex])
        {
            FSlateBrush Brush = CooldownOverlays[SkillIndex]->GetBrush();
            Brush.ImageSize = FVector2D(Brush.ImageSize.X, SkillImage1->GetDesiredSize().Y * Percent);
            CooldownOverlays[SkillIndex]->SetBrush(Brush);

            CooldownOverlays[SkillIndex]->SetOpacity(0.5f);
        }
    }

}
