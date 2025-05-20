// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/Dragon.h"
//-----추가-----
#include "Base/MyGameInstance.h"
#include "Player/MyPlayer.h"
#include "EngineUtils.h"
#include "GameFramework/PlayerController.h"

#include "../Animation/PlayerAnimInstance.h"
#include "../Animation/DragonAnimInstance.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Kismet/GameplayStatics.h"
#include "MyPlayerController.h"
#include "../Animation/BaseAnimInstance.h"
#include "Monster/Monster.h"


#include "Base/Managers/UIManager.h"
#include "UI/StatWidget.h"
#include "UI/PlayerBarWidget.h"
#include "Components/WidgetComponent.h"
#include "Components/ProgressBar.h"


ADragon::ADragon()
{
	PrimaryActorTick.bCanEverTick = true;
	_knightInstance = nullptr;

    // 드래곤의 비행을 위해 중력 제거
    
    GetCapsuleComponent()->InitCapsuleSize(230.0f, 230.0f);
    GetCharacterMovement()->bOrientRotationToMovement = false;
    GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);
    
    _springArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
    _camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    
    _springArm->SetupAttachment(RootComponent);
    _camera->SetupAttachment(_springArm);

    _springArm->TargetArmLength = 1200.0f;
    _springArm->SetRelativeRotation(FRotator(-35.0f, 0.0f, 0.0f));

    _springArm->bUsePawnControlRotation = false;
    _camera->bUsePawnControlRotation = false;

    bUseControllerRotationYaw = false;

    static ConstructorHelpers::FObjectFinder<USkeletalMesh> DragonMeshAsset(TEXT("/Script/Engine.SkeletalMesh'/Game/QuadrapedCreatures/MountainDragon/Meshes/SK_MOUNTAIN_DRAGON.SK_MOUNTAIN_DRAGON'"));
    if (DragonMeshAsset.Succeeded())
    {
        GetMesh()->SetSkeletalMesh(DragonMeshAsset.Object);
    }

    GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, -230.0f)); // 예: 메쉬를 살짝 아래로 배치
    GetMesh()->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));



    static ConstructorHelpers::FClassFinder<UStatWidget> StatClass(
        TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Blueprint/UI/PlayerStat_UI.PlayerStat_UI_C'"));
    if (StatClass.Succeeded())
    {
        _statWidget = CreateWidget<UStatWidget>(GetWorld(), StatClass.Class);
    }

    if (WidgetClass)
    {
        _Widget = CreateWidget<UPlayerBarWidget>(GetWorld(), WidgetClass);
        if (_Widget)
        {
            _Widget->AddToViewport();
        }
    }

}

void ADragon::BeginPlay()
{
	Super::BeginPlay();

    for (TActorIterator<AMyPlayer> It(GetWorld()); It; ++It)
    {
        _knightInstance = *It;
        if (_knightInstance)
        {
            UE_LOG(LogTemp, Warning, TEXT("KnightInstance found and assigned!"));
            break;
        }
    }

    if (!_knightInstance)
    {
        UE_LOG(LogTemp, Error, TEXT("KnightInstance not found in the world!"));
        return;
    }

    // Dragon 초기화
    SetActorHiddenInGame(true);
    SetActorEnableCollision(false);
    _isTransformed = false;

}




void ADragon::TransformToHuman()
{
     if (APlayerController* PC = Cast<APlayerController>(GetController()))
    {
        // 상태 복원
        _knightInstance->SetActorLocation(GetActorLocation());  // 현재 Dragon의 위치로 복원
        _knightInstance->SetActorRotation(GetActorRotation());

        // MyPlayer 활성화
        _knightInstance->SetActorHiddenInGame(false);
        _knightInstance->SetActorEnableCollision(true);

        // Dragon 비활성화
        SetActorHiddenInGame(true);
        SetActorEnableCollision(false);

        // 컨트롤 전환
        PC->Possess(_knightInstance);

        // 상태 업데이트
        _isTransformed = false;
        _knightInstance->_isTransformed = false;

        UE_LOG(LogTemp, Warning, TEXT("Transformed back to MyPlayer!"));
    }

}

void ADragon::TransformToDragon()
{
    // MyPlayer에서 Dragon으로 복귀
    _knightInstance->TransformToDragon();
}

void ADragon::ToggleTransformation()
{
    if (_isTransformed) // 현재 변환된 상태이면 인간으로 복귀
    {
        TransformToHuman();
    }
    else // 그렇지 않으면 드래곤으로 변환
    {
        TransformToDragon();
    }
}

void ADragon::OnMonsterHit(AMonster* HitMonster, const FHitResult& Hit)
{
    if (HitMonster)
    {
        FVector LaunchDirection = (HitMonster->GetActorLocation() - GetActorLocation()).GetSafeNormal();
        HitMonster->LaunchFromPlayer(LaunchDirection);
    }
}

void ADragon::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
    {
        EnhancedInputComponent->BindAction(_moveAction, ETriggerEvent::Triggered, this, &ADragon::Move);
        EnhancedInputComponent->BindAction(_lookAction, ETriggerEvent::Triggered, this, &ADragon::Look);
        EnhancedInputComponent->BindAction(_jumpAction, ETriggerEvent::Triggered, this, &ADragon::JumpA);
        EnhancedInputComponent->BindAction(_Change, ETriggerEvent::Started, this, &ADragon::ToggleTransformation);
        EnhancedInputComponent->BindAction(_attackAction, ETriggerEvent::Started, this, &ADragon::AttackA);
    
    }
}

void ADragon::Move(const FInputActionValue& value)
{
    // fly할때 isFalling 통해서 생각해볼것..
    FVector2D MovementVector = value.Get<FVector2D>();
           
    if (Controller && MovementVector.Size() > 0.0f)
    {
        // 이동 방향 벡터 계산
        const FRotator ControlRotation = Controller->GetControlRotation();
        const FRotator YawRotation(0, ControlRotation.Yaw, 0);

        const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
        const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

        AddMovementInput(ForwardDirection, MovementVector.Y); // 전진/후진
        AddMovementInput(RightDirection, MovementVector.X);   // 좌우 이동
    }
}

void ADragon::Look(const FInputActionValue& value)
{
    FVector2D LookAxisVector = value.Get<FVector2D>();

    AddControllerYawInput(LookAxisVector.X); // 좌우 회전
    AddControllerPitchInput(LookAxisVector.Y); // 상하 회전

}

void ADragon::JumpA(const FInputActionValue& value)
{
    bool isPressed = value.Get<bool>();

    if (isPressed)
    {
        if (GetCharacterMovement()->IsFalling())
        {
            // 공중에서 추가 비행 (날갯짓)
            FVector ForwardInput = GetActorForwardVector() * GetInputAxisValue("MoveForward");
            FVector RightInput = GetActorRightVector() * GetInputAxisValue("MoveRight");
            FVector JumpImpulse = ForwardInput * 300.0f + RightInput * 300.0f + FVector(0.0f, 0.0f, 500.0f);

            LaunchCharacter(JumpImpulse, true, true);
        }
        else
        {
            // 지상에서 점프
            ACharacter::Jump();

            // 공중 제어 및 중력 설정
            GetCharacterMovement()->GravityScale = 0.5f; // 느린 하강
            GetCharacterMovement()->AirControl = 0.8f;    // 공중 제어 강화
            GetCharacterMovement()->MaxFlySpeed = 800.0f; // 공중 속도 증가
         }

        // 애니메이션 상태 업데이트: 점프 시작
        _dragonAnimInstance->SetJumping(true);
    }
    else
    {
        if (!GetCharacterMovement()->IsFalling())
        {
            // 착지 시 중력 및 이동 속도 복원
            GetCharacterMovement()->GravityScale = 1.0f;
            GetCharacterMovement()->AirControl = 0.2f; // 기본 공중 제어 값
            GetCharacterMovement()->MaxFlySpeed = 600.0f; // 기본 속도 복원
            
            // 애니메이션 상태 업데이트: 착지
            _dragonAnimInstance->SetJumping(false);
        }
    }
}

void ADragon::AttackA(const FInputActionValue& value)
{
    bool isPressed = value.Get<bool>();
    if (isPressed && _isAttacking == false && _dragonAnimInstance != nullptr)
    {
        _dragonAnimInstance->PlayAttackMontage();
        _isAttacking = true;

        _curAttackIndex %= 2;
       // _curAttackIndex++;


        if (GetCharacterMovement()->IsFalling())  // 점프 중이면 IsFalling()이 true를 반환
        {
            _dragonAnimInstance->JumpToSection(2);  // 점프 상태일 때 섹션 2
        }
        else
        {
            _dragonAnimInstance->JumpToSection(1);  // 점프 상태가 아닐 때 섹션 1
        }
    }


}

void ADragon::PostInitializeComponents()
{
    Super::PostInitializeComponents();

      // 애니메이션 인스턴스 클래스를 설정
    if (DragonAnimInstanceClass)
    {
        USkeletalMeshComponent* MeshComp = GetMesh();
        if (MeshComp)
        {
            MeshComp->SetAnimInstanceClass(DragonAnimInstanceClass);
        }
    }

    // 애니메이션 인스턴스 캐스팅
    _dragonAnimInstance = Cast<UDragonAnimInstance>(GetMesh()->GetAnimInstance());
    if ( _dragonAnimInstance->IsValidLowLevelFast())
    {
        // 애니메이션 몽타주 끝났을 때 처리할 델리게이트 연결
        _dragonAnimInstance->OnMontageEnded.AddDynamic(this, &ADragon::OnAttackEnded);


        _dragonAnimInstance->_attackDelegate_Dragon.AddUObject(this, &ACreature::AttackHit);
        // 드래곤 사망 델리게이트 연결
        _dragonAnimInstance->_deathDelegate_Dragon.AddUObject(this, &ADragon::Disable);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Failed to initialize _dragonAnimInstance for ADragon!"));
    }

    // TODO
    //----------------------------------------------임시 dragon state으로 일단세팅----------------------
    if (_StatCom)
    {
        _StatCom->SetDragonLevelInit(1);
    }
    //------------------------------------------------------------------------------------------

}

void ADragon::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);


    if (_StatCom->IsDead())
        return;


    if (GetVelocity().Size() > 0.0f)
    {
        FRotator NewRotation = GetActorRotation();
        NewRotation.Yaw = FMath::Atan2(GetVelocity().Y, GetVelocity().X) * 180.0f / PI;  // 이동 방향에 맞게 회전
        SetActorRotation(NewRotation); // 회전 적용
    }

}

float ADragon::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{

    Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);


    return 0.0f;
}
