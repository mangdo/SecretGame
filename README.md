# SecretGame
> SDL을 사용한 '선생님 몰래 게임하기' 게임입니다.   
> 3학년 1학기, '게임 프로그래밍' 수업에서 진행한 팀 프로젝트입니다.

<br>

## 1. 제작 기간 & 참여 인원
- 2019년 4월 9일 ~ 2019년 6월 3일
- 3인 1조 팀 프로젝트

<br>

## 2. 사용 기술
  - C++
  - SDL 2

<br>

## 3. 게임 방법

<img width="650" alt="howtogame1" src="https://user-images.githubusercontent.com/70243735/117093814-02993d80-ad9d-11eb-9ad3-63b664afe3db.jpg">
<img width="650" alt="howtogame" src="https://user-images.githubusercontent.com/70243735/117093834-0f1d9600-ad9d-11eb-8b28-d2ecf945ff0e.jpg">

<br>

## 4. 게임 플레이 영상

[![https://youtu.be/vhf6FUwvVSY](https://user-images.githubusercontent.com/70243735/117094335-84d63180-ad9e-11eb-9b1f-b42d35ac41f5.png)](https://youtu.be/vhf6FUwvVSY)

<br>

## 5. 게임의 차별화 요소

* **추억 속의 그 게임**
  
  <img src ="https://user-images.githubusercontent.com/70243735/117094509-ef876d00-ad9e-11eb-81a1-3c372c6e988e.png" width ="600px">
  
  &nbsp; 컴퓨터실에서 선생님 몰래하던 플래시 게임을 재현하여 **90년대생들의 향수를 자극**하였습니다.   
  단순히 플래시 게임을 재현하는 것보다 **게임 속의 게임**으로 만들어서 재미요소를 더하였습니다.   
  메인게임과 미니게임의 구별을 뚜렷하게 하기 위하여 메인게임은 일러스트 이미지로, 미니게임은 픽셀이미지로 제작하였습니다.   

* **여러가지 엔딩**
  
  <img src ="https://user-images.githubusercontent.com/70243735/117094579-1ba2ee00-ad9f-11eb-8f5e-2ea8cc818936.png" width ="600px">
  
  &nbsp; 플래시 게임은 여러번 실패하고 여러번 도전하는 특징을 가지고 있습니다.   
  때문에 '다시시작'기능을 구현하였으며 여러가지 엔딩을 준비하였습니다.    
  특히, 수업시간동안 한번도 게임을 플레이하지않으면 선생님에게 A+을 받는 **히든엔딩**도 숨어있습니다.   

* **피드백을 수용하며 높은 완성도**

  <img src ="https://user-images.githubusercontent.com/70243735/117094617-37a68f80-ad9f-11eb-97cb-de196ebce248.png" width ="600px">

  '게임 프로그래밍'수업을 수강하는 학우들에게 익명의 동료평가를 받으며 게임의 컨셉에 대한 피드백을 수용하였습니다.   
  또한 다른 학과의 친구들에게도 게임을 보내주며, 피드백을 받아 게임의 난이도를 조정하고 설명을 추가하는등 게임을 완성도를 높여갔습니다.

<br>

## 6. 핵심 트러블 슈팅
### 6.1. 공통으로 사용되는 클래스 :video_game:
 문제 상황   
* 확대 화면, 축소화면 두 개의 화면에서는 게임의 캐릭터, 아이템 요소들을 공통으로 사용하고 있습니다.
* 화면이 바뀔때마다 직접 변수 값들로 주고 받는 것은 번거로웠고 중복되는 코드가 많았습니다.

해결   
<img src = "https://user-images.githubusercontent.com/70243735/117094697-6e7ca580-ad9f-11eb-9983-e22dcb2f008b.png" width ="600px">

* **싱글톤 패턴**을 적용하였습니다.
* **생성자를 private로** 만들어 객체를 하나만 생성하도록 구현하였습니다.
* 그렇게 만들어진 객체를 확대화면, 축소화면에서 **GetSingleton()** 으로 접근합니다.

<details>
<summary>코드 확인 :pushpin: </summary>
  
[GameClassStage1.h](./GameByClass/GameClassStage1.h) 
```C++
class Stage1
{
private:
  MyCharacter *my;
  Teacher *cha;
  ItemManager *itemM;
  
  // (생략)
}
```

[GameClassStage1.cpp](./GameByClass/GameClassStage1.cpp)

```C++
Stage1::Stage1()
{
  MyCharacter::CreateInstance(); // MyCharacter의 클래스는 객체를 한번만 만들 예정.
  my = MyCharacter::GetSingleton();

  Teacher::CreateInstance(); // teacher클래스역시 한번만 만들어줌.
  cha = Teacher::GetSingleton();

  ItemManager::CreateInstance(); // itemmanager(아이템벡터)클래스역시 한번만 만들어줌.
  itemM = ItemManager::GetSingleton();
  
  // (생략)
}

void Stage1::Update() 
{
  my->Update(); // 내 캐릭터 변동사항 업데이트
  itemM->Update();
  cha->Update();
  
  // (생략)
}
```

</details>

### 6.2. 아이템 :alarm_clock: :shoe: :gift_heart:
문제 상황   
* 게임 속에 등장하는 아이템들은 종류마다 다른 속도, 무게, 이미지를 가지고 있습니다. 때문에 모두 다른 클래스로 만들었습니다.
* 하지만 장애물과 아이템들은 이동, 삽입, 삭제등 공통된 기능을 가지고 있어서 같은 코드가 중복적으로 사용되고 있었습니다.

해결
* 장애물과 아이템을 효율적으로 다루기 위해 벡터를 이용하였습니다.
* 벡터, 데큐, 리스트 중 게임의 특성상 중간값을 건드리는 일보다도 차례대로 넣고 차례대로 빼기 때문에 **벡터**를 선택하였습니다.
* 벡터가 제공하는 함수 중 erase(), begin(), size(), at() 함수를 필요한 상황에 찾아서 가져다가 사용하였습니다.

<details>
<summary>코드 확인 :pushpin: </summary>

[ItemManager.h](/GameByClass/ItemManager.h)

```c++
class ItemManager {
public:
  vector <Item> v;

  // (생략)
}
```
[ItemManager.cpp](./GameByClass/ItemManager.cpp)
```C++
void ItemManager::Update() {

// 화면 끝에 도달시 벡터 요소 삭제
if (v.size() != 0) { // 벡터의 크기가 0이 아니라면
  for (int n = 0; n < v.size(); n++) {
    v.at(n).Update(); // 벡터 요소 하나하나를 다 위치 업뎃
      if (v.at(n).x <= 330) { // 컴퓨터 화면의 끝에 도달하면
        vector<Item>::iterator it = v.begin() + n; // 그 벡터 요소는 없애버림
        v.erase(it);
      }
    }
  }

  // (생략)
}

void ItemManager::Move() {
  if (v.size() != 0) {
    for (int n = 0; n < v.size(); n++) {
      v.at(n).Move();
    }
  }
  
  // (생략)
}
```

</details>


### 6.3. 일정 구간에서 랜덤으로 생성되는 아이템 :gift:
문제 상황
* 아이템과 장애물은 사용자가 패턴을 알 수 없도록 **랜덤**하게 나타나야 합니다.
* 장애물들은 **똑같은 확률로 랜덤**하게 나와도 괜찮았지만,
* 아이템의 경우에는 각 특징이 달랐기때문에 **나오는 확률이 달라야했습니다.**
* 예를 들어 시간을 늘려주는 아이템은 여러번 나와도 괜찮지만, 받은 경고를 삭제해주는 아이템은 적게 나와야했습니다.

해결

<img src = "https://user-images.githubusercontent.com/70243735/117094763-9d931700-ad9f-11eb-8d6c-b25c8f0a43a5.png" width ="600px">

* rand()함수 값을 나머지 연산을 통해 원하는 랜덤값을 얻어냅니다.
* 아이템의 경우 원하는 랜덤값을 1~10으로 받아 구간으로 사용합니다.

<details>
<summary>코드 확인 :pushpin: </summary>

[ItemManager.cpp](./GameByClass/ItemManager.cpp)
```C++  
ItemManager::ItemManager() {
  srand((unsigned int)time(NULL));//랜덤 수

  // (생략)
}

void ItemManager::Update() {

  // 장애물 만들어서 벡터에 넣기.
  if (distancecount <= gDis->distance) { // 랜덤 거리 지날때마다 다시 정의
    lastBlock = gDis->distance; // 장애물을 만든 위치 저장.

    int n = rand() % 4; // 3~6칸마다
    distancecount = gDis->distance + n + 3; // distancecount 다시정의
    int item_n = rand() % 4; // 장애물의 종류는 4개(0,1,2,3) 

    int item_y = rand() % 3; // y좌표는 0 1 2중 하나 랜덤.
    Item tempitem(item_n, item_y); // 새 아이템 객체만들어서

    v.push_back(tempitem); // 벡터의 맨뒤에 넣기
  }
  
  // 아이템은 랜덤으로 또 만든다. 하지만, 장애물을 이미 만든 distancecount라면 넘어간다.
  if (itemCount <= gDis->distance) {

    if (gDis->distance == lastBlock) { // 장애물을 만들었던 위치와 동일하다면
      itemCount = lastBlock + 2; // 지금 말고 장애물 나오고 2칸 다음에
    }
    else {
      int n = rand() % 5; // 20~25칸마다 아이템 나옴.
      itemCount = gDis->distance + n + 20; // 재정의
      int item_tmp_n = rand() % 10;
      int item_y = rand() % 3; // y좌표는 0 1 2중 하나 랜덤.
      int item_n;

      if (0 <= item_tmp_n && item_tmp_n < 5) // 확률로 나오게끔.
        item_n = 4;
      else if (5 <= item_tmp_n && item_tmp_n < 9)
        item_n = 5;
      else if (item_tmp_n = 10)
        item_n = 6;
      Item tempitem(item_n, item_y); // 새 아이템 객체만들어서
      v.push_back(tempitem); // 벡터의 맨뒤에 넣기
    }
  }
  
  // (생략)
}
```

</details>
