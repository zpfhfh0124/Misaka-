#include "stdafx.h"
#include "playGround.h"
#include "fieldStage.h"
#include "bossStage.h"

playGround::playGround()
{
}


playGround::~playGround()
{
}

//초기화 함수
HRESULT playGround::init()
{
	gameNode::init(true);


	// * 이미지 추가
	// ** 배경
	IMAGEMANAGER->addImage("원경", "images/배경/Academy_City_(Aerial_View)_단축_1200x800.bmp", 1200, 800, true, RGB(0, 0, 0));
	IMAGEMANAGER->addImage("근경", "images/배경/도시 근경2.bmp", 5000, 800, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("보스전배경", "images/배경/battleAccel.bmp", 1200, 800, true, RGB(255, 0, 255));
	// ** 지형
	IMAGEMANAGER->addImage("필드지형처리", "images/장애물 오브젝트/map_ground.bmp", 5000, 800, true, RGB(0, 255, 255));
	IMAGEMANAGER->addImage("보스전지형처리", "images/장애물 오브젝트/battleAccel_ground.bmp", 1200, 800, true, RGB(0, 255, 255));
	IMAGEMANAGER->addImage("포탈", "images/장애물 오브젝트/포탈.bmp", 130, 200, true, RGB(255, 0, 255));
	
	// ** 몬스터
	// *** 일반몬스터
	IMAGEMANAGER->addFrameImage("라츠", "images/몬스터/라츠_resize.bmp", 980, 200, 7, 2, true, RGB(0, 255, 0));
	// *** 보스캐릭
	IMAGEMANAGER->addFrameImage("액셀기본", "images/캐릭터/ACCEL/ACCEL_IDLE.bmp", 400, 360, 4, 2, true, RGB(0, 255, 0));
	IMAGEMANAGER->addFrameImage("액셀이동", "images/캐릭터/ACCEL/ACCEL_MOVE.bmp", 1200, 300, 6, 2, true, RGB(0, 255, 0));
	IMAGEMANAGER->addFrameImage("액셀패턴공격", "images/캐릭터/ACCEL/ACCEL_PATTERN.bmp", 735, 480, 3, 2, true, RGB(0, 255, 0));
	IMAGEMANAGER->addFrameImage("액셀공격반사", "images/캐릭터/ACCEL/ACCEL_REFLECT.bmp", 240, 360, 2, 2, true, RGB(0, 255, 0));
	IMAGEMANAGER->addFrameImage("액셀기절", "images/캐릭터/ACCEL/ACCEL_FALLDOWN.bmp", 400, 80, 2, 1, true, RGB(0, 255, 0));
	IMAGEMANAGER->addFrameImage("흑익", "images/캐릭터/ACCEL/ACCEL_VECTOR_re.bmp", 600, 306, 1, 2, true, RGB(0, 255, 0));
	// *** 플레이어 캐릭
	IMAGEMANAGER->addFrameImage("레일건", "images/캐릭터/MIKOTO/MIKOTO_RAILGUN_re.bmp", 800, 160, 1, 2, true, RGB(0, 255, 0));

	// **** UI
	//체력, 마나 게이지
	IMAGEMANAGER->addImage("보스게이지바탕", "images/UI/보스게이지_바탕_re.bmp", 1080, 70, false, RGB(0, 0, 0));
	IMAGEMANAGER->addImage("플레이어HP게이지바탕", "images/UI/HP게이지_바탕.bmp", 230, 30, false, RGB(0, 0, 0));
	IMAGEMANAGER->addImage("플레이어CP게이지바탕", "images/UI/CP게이지_바탕.bmp", 230, 30, false, RGB(0, 0, 0));


	//사운드 추가
	SOUNDMANAGER->addSound("필드BGM", "sounds/nightmare.mp3", true, true);
	SOUNDMANAGER->addSound("보스BGM", "sounds/Accelerator.mp3", true, true);


	//클래스 동적할당
	_player = new player;
	_player->init();

	_boss = new boss;
	//_boss->init();

	/*_pixel = new pixelCollsion;
	_pixel->init();*/

	//_enemyMg = new enemyManager;
	//_enemyMg->init();
	//_enemyMg->setEnemy();

	_stage = new fieldStage;	// 맨 처음 스테이지 설정
	_stage->enter(_player);		//플레이어 클래스를 전달하여 초기화
	_player->setStageAddressLink(_stage);
	_player->setBossAddressLink(_boss);
	_boss->setPlayerAddressLink(_player);
	// _enemyMg->setPlayerMemoryAddress(_player);
	// _stage->setEnemyMgAddressLink(_enemyMg);

	// CAMERA->setPosition(_player->getPlayerX(), _player->getPlayerY());
	
	return S_OK;
}

//메모리 해제
void playGround::release()
{
	
}

//연산
void playGround::update()
{
	gameNode::update();

	_player->update();
	// _pixel->update();
	// _enemyMg->update();

	//newStage가 변함이 없다면 현재 스테이지
	//newStage에 새로운 포인터값이 들어오면
	//현재 스테이지 삭제 및 새 스테이지 호출
	stage* newStage = _stage->updateStage(); 
	if (newStage != nullptr)
	{
		//_stage->exit();		// 동적할당등 사라지기 전에 해야 할 거
		delete _stage;
		_stage = newStage; // 새로운 스테이지로 변경
		_stage->enter(_player); // 새로운 스테이지에서 초기화 할거
		_stage->enterBoss(_boss);
		_player->setStageAddressLink(_stage);
		// _pixel->setStageAddressLink(_stage);
	}

	
}

//그리기 전용
void playGround::render()
{	
	//카메라 프레임 이동 추가
	PatBlt(getMemDC(), 0, 0, getMemDCWidth(), getMemDCHeight(), WHITENESS);
	PatBlt(CAMERA->getMemDC(), 0, 0, getMemDCWidth(), getMemDCHeight(), WHITENESS);
	
	//=================================================

	_stage->render();
	// _pixel->render();
	_player->render();
	// _enemyMg->render();
	
	//=============================================
	_backBuffer->render(CAMERA->getMemDC(), 0, 0,
		CAMERA->getLeft(), CAMERA->getTop(),
		CAMERA->getWidth(), CAMERA->getHeight());
	CAMERA->render(getHDC());
}
