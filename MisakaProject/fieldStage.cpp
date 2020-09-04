#include "stdafx.h"
#include "fieldStage.h"
#include "bossStage.h"
#include "player.h"
#include "enemyManager.h"

void fieldStage::pixelCollision()
{
	float pX = _player->getPlayerX();
	float pY = _player->getPlayerY();

	//탐사축도 업데이트 함수에 넣어서 계속해서 갱신해준다
	float probeY = pY + _player->getPlayerRectHeight() / 2; //플레이어 렉트의 바텀 부분

	for (int i = probeY - 5; i < probeY + 5; ++i)
	{
		COLORREF color;
		color = GetPixel(getPixelImage()->getMemDC(), pX, i);

		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if (!(r == 0 && g == 255 && b == 255))
		{
			//픽셀 지형에 충돌
			_player->setPlayerY(i - _player->getPlayerRectHeight() / 2);
			_player->setPlayerGround(true);
			break;
		}
		else _player->setPlayerGround(false);
	}
}

fieldStage::fieldStage()
{
}

fieldStage::~fieldStage()
{
}

void fieldStage::release()
{
}

//초기화
void fieldStage::enter(player * player)
{
	CAMERA->init(WINSIZEX, WINSIZEY, 5000, 800);

	//배경음
	SOUNDMANAGER->play("필드BGM", 0.7f);

	stage::enter(player);

	_pixelImg = IMAGEMANAGER->findImage("필드지형처리");
	_isClear = false;
	_minX = 0;
	_maxX = 5000;
	_portal = RectMakeCenter(4800, WINSIZEY - 170, 130, 200);
	_portalImg = IMAGEMANAGER->findImage("포탈");

	_enemyMg = new enemyManager;
	_enemyMg->setPlayerMemoryAddress(player);
	_enemyMg->init();
	_enemyMg->setEnemy();

	/*for (int i = 0; i < FENCEMAX; i++)
	{
		_fence[i] = RectMakeCenter(_fencePoint[i].x, _fencePoint[i].y, 50, 50);
	}*/
}

void fieldStage::exit()
{
}

stage* fieldStage::updateStage()
{
	pixelCollision();
	//_enemyMg->update();

	//포탈 진입
	RECT temp;
	if (IntersectRect(&temp, &_player->getRect(), &_portal))
	{
		//포탈 진입 후 보스 스테이지로 전환
		if (KEYMANAGER->isOnceKeyDown(VK_UP) && _isClear)
		{
			return new bossStage;
		}
	}
	
	if (_enemyMg->getEnemyVectorSize() == 0)
	{
		_isClear = true;
	}
	_enemyMg->update();

	CAMERA->setPosition(_player->getPlayerX(), _player->getPlayerY());

	return nullptr;
}

void fieldStage::render()
{
	IMAGEMANAGER->findImage("원경")->render(getMemDC(), CAMERA->getLeft(), CAMERA->getTop());
	IMAGEMANAGER->findImage("근경")->render(getMemDC());
	IMAGEMANAGER->findImage("필드지형처리")->render(getMemDC(), 0, 0);
	_portalImg->render(getMemDC(), _portal.left, _portal.top);
	_enemyMg->render();
	//Rectangle(getMemDC(), _portal);

	/*for (int i = 0; i < FENCEMAX; i++)
	{
		Rectangle(getMemDC(), _fence[i]);
	}*/

	/*char str[128];
	sprintf_s(str, "남은 적 : %d", _enemyMg->getEnemyVectorSize());
	TextOut(getMemDC(), CAMERA->getLeft() + 700, 100, str, strlen(str));*/
}
