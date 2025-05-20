# Y2PK_Team_RPG

🔗 [유튜브 플레이 영상 보기](https://www.youtube.com/watch?v=NWj8hIFVd30)

## 📅 프로젝트 정보

- **기간**: 2024년 10월 17일 ~ 2024년 12월 11일 
- **인원**: 총 4명 (모두 프로그래머로 구성)

## 📌 프로젝트 개요

본 프로젝트는 **7주간 개발된 언리얼 엔진 기반 3D 던전 루프형 액션 RPG 게임**입니다.  
총 4인 팀이 참여하여 GitHub를 기반으로 협업과 버전 관리를 수행하였으며,  
모든 주요 시스템은 **C++과 언리얼 블루프린트**를 병행해 직접 구현하였습니다.

### 🎮 게임 구조

플레이어는 **마을에서 아이템을 구매하거나 장비를 정비한 후**,  
스테이지로 출전하여 몬스터와 전투를 벌이고,  
**전리품(골드, 아이템)을 챙겨 마을로 귀환**하는 루프를 반복합니다.  

게임은 총 **5개 지역(마을 → 스테이지1 → 보스1 → 스테이지2 → 보스2)** 으로 구성되어 있으며,  
각 지역은 고유한 몬스터 AI, 스킬 패턴, 전투 연출, UI를 포함합니다.

### ⚙️ 주요 구현 요소
- **AIController + Behavior Tree**를 활용한 몬스터 전투 로직
- **마을/NPC 상호작용 기반 상점 시스템**
- **스탯/장비/인벤토리 기반 전투 성장 구조**
- **다양한 위젯 기반 UI (체력바, 경험치, 상점, 스킬, 미니맵 등)**

아래는 전체 클래스 구조를 정리한 내용입니다.

### 🔍 클래스 구조도
 MyGameInstance (게임 단계 및 전역 데이터 관리)

- AActor  
  ├── AEffectManager (이펙트 관리)  
  ├── ASoundManager (사운드 관리)  
  ├── AUIManager (UI 전체 관리)  
  ├── AGameModeBase (게임 진행 관리)  
  │   ├── AStartGameModeBase (시작 화면 모드)  
  │   ├── AMyGameModeBase (기본 플레이 모드)  
  │   │   ├── AStage1NormalGameModeBase (스테이지 1 일반)  
  │   │   ├── AStage2NormalGameModeBase (스테이지 2 일반)  
  │   ├── ABossGameModeBase (보스전 모드)  
  │   │   ├── AStage1BossGameModeBase (스테이지 1 보스)  
  │   │   ├── AStage2BossGameModeBase (스테이지 2 보스)  
  ├── AMyCreature (ACharacter 상속)  
  │   ├── AMyPlayer (플레이어 캐릭터)  
  │   │   ├── ADragon (특수 조작 캐릭터)  
  │   ├── AMyMonster  
  │   │   ├── ANormalMonster  
  │   │   ├── EpicMonster_witch  
  │   │   ├── ABossMonster  
  │   │   ├── ABoss2Monster  
- AMyComponent  
  ├── UStatComponent (스탯 관리)  
  ├── UInventoryComponent (인벤토리 시스템)  
  ├── UShopComponent (상점 기능)  
- ABaseItem  
  ├── AEquipItem (장비 아이템)  
  │   ├── Helmet, ShoulderGuard, UpperArmor, LowerArmor  
  │   ├── Sword, Shield  
  ├── AConsumeItem (소비 아이템)  
  │   ├── Gold, HP_Potion  
- AnimationInstance  
  ├── BaseAnimInstance  
  ├── PlayerAnimInstance  
  ├── Monster_N / Boss01 / Boss2 / Epic01  
  ├── DragonAnimInstance  
- PlayerController  
  ├── MyPlayerController (UI 및 입력)  
  ├── Portal  
  │   ├── Portal_Home / Stage1 / Stage2_Normal / Stage2_Boss  
- NPC  
  ├── AMyNPC (상호작용 NPC)  
  ├── NPC_NameWidget (이름 위젯)  
- MonsterAI  
  ├── AIController_NormalMonster / BossMonster / Boss2 / Epic  
  ├── BehaviorTree  
  │   ├── BTDecorator_CanAttack / Stun  
  │   ├── BTService_FindTarget / CheckHP / PlayerDistance  
  │   ├── BTTaskNode_Attack / Fireball / Teleport / Summoning / Dash 등  
- UI  
  ├── PlayerBarWidget, InventoryWidget, ShopWidget, StatWidget  
  ├── Boss1Widget / Boss2Widget / MainStartWidget / MiniMapWidget  
  ├── SkillWidget_test, IconTestWidget  
  ├── Elements: IndexedButton  
- 기타  
  ├── Fireball, MeteorDecal, MeteorDecalPool  
  ├── Stage 포탈 


## 🔥 맡은 역할

### 🎮 플레이어 및 NPC 구현
- 기사(근접), 궁수(원거리), NPC 캐릭터 클래스 설계 및 구현

### 🧑‍💻 UI 시스템 연동
- 체력/경험치 UI와 캐릭터 Stat 컴포넌트 연동 (델리게이트 활용)
- Inventory UI 및 Store UI 설계 및 이벤트 처리 구현

### 🏪 상점 시스템 구성
- NPC와 상호작용 시 Store UI 호출
- 상점 아이템 구매 로직 처리 및 인벤토리 추가 연동

### 🧠 NPC AI 및 적대 관계 처리
- NPC AIController 구현
- NPC와 Player 간 거리에 따른 상호작용 설정
- 적대관계 NPC가 피해를 받으면 Blackboard 상태 변경


NPC 구현
- NPC 상점 구현
- 플레이어가 NPC 공격시 적대관계로 변환
- NPC Behavior Tree 설계 및 AI 패턴 적용

📌 Blackboard의 "IsDamaged" 키가 true가 되면, NPC는 전투 상태로 진입
```cpp
// 피해를 받으면 AI에게 적대 상태 알림
if (auto NpcController = Cast<AMyNPCAIController>(GetController()))
{
    if (NpcController && NpcController->GetBlackboardComponent())
    {
        NpcController->GetBlackboardComponent()->SetValueAsBool(FName(TEXT("IsDamaged")), true);
    }
}
```
📌 AI가 적대 상태일 때 호출되는 함수로, NPC가 공격 몽타주를 실행  
```cpp
// 적대 상태일 경우 공격 시작  

void AMyNPC::Attack_AI()
{
    if (_statCom->IsDead()) return;

    if (!_isAttcking && _animInstance)
    {
        _animInstance->PlayAttackMontage();
        _isAttcking = true;

        _curAttackIndex %= 3;
        _curAttackIndex++;
        _animInstance->JumpToSection(_curAttackIndex);
    }

}
```

🛠️ 오류 상황 및 해결 방안    
  
❗ 오류 상황: GitHub 협업 중 충돌 발생  
- 프로젝트 초기에 GitHub Desktop을 통해 협업을 진행하던 중, 팀원 간 소통 부족으로 동시에 main 브랜치에 merge를 시도  
이로 인해 코드 충돌이 발생, 일부 파일이 꼬이고 게임 실행에 오류가 발생  


✅ 해결 방안: 역할 분담 + Git 사용 방식 개선  
- 주간 회의를 통해 각자의 진행 상황을 공유  
- 역할 분담 : 역할별로 브런치를 만들어 작업
- pull 전 습관화: push 전에 항상 pull 받고, 충돌 여부를 확인  
- Develop 브랜치에서 병합 및 버그 테스트 후 Main 브랜치로 반영


## 📚 프로젝트를 통해 배운 점  
  
🤝 협업 경험  
- GitHub 충돌 상황을 통해 브랜치 전략과 소통의 중요성 체감  
- feature 브랜치, 주간 회의, 역할 분담 등을 통한 협업 능력 향상  
- 충돌 해결과 PR 경험을 통해 실전 Git 협업 방식 학습  
  
⚙️ 기술 역량 강화  
- 언리얼 엔진 기반 C++ 클래스 구조 설계 및 컴포넌트 활용  
- Behavior Tree를 활용한 NPC AI 상태 머신 구현  
- UI 시스템과 델리게이트 연동을 통해 이벤트 기반 처리 구현  

💡 종합적 성장
- 제한된 기간 안에서 기획 → 구현 → 문제 해결을 경험
- 시스템 구조와 역할 분배의 중요성을 실무적으로 학습


