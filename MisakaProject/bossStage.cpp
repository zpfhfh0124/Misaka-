#include "stdafx.h"
#include "bossStage.h"
#include "player.h"
#include "boss.h"

void bossStage::pixelCollision()
{
	float pX = _player->getPlayerX();
	float pY = _player->getPlayerY();
	float bX = _boss->getBossX();
	float bY = _boss->getBossY();

	//탐사축도 업데이트 함수에 넣어서 계속해서 갱신해준다
	//플레이어의 픽셀충돌 검사
	float probePY = pY + _player->getPlayerRectHeight() / 2; //플레이어 렉트의 바텀 부분

	for (int i = probePY - 5; i < probePY + 5; ++i)
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

	//보스캐릭의 픽셀충돌 검사
	float probeBY = bY + _boss->getRectHeight() / 2;

	for (int i = probeBY - 5; i < probeBY + 5; ++i)
	{
		COLORREF color;
		color = GetPixel(getPixelImage()->getMemDC(), bX, i);

		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if (!(r == 0 && g == 255 && b == 255))
		{
			//픽셀 지형에 충돌
			_boss->setBossY(i - _boss->getRectHeight() / 2);
			_boss->setIsGround(true);
			break;
		}
		else _boss->setIsGround(false);
	}
}


bossStage::bossStage()
{
}

bossStage::~bossStage()
{
}

//HRESULT bossStage::init()
//{
//	return S_OK;
//}

void bossStage::release()
{
}

void bossStage::enter(player * player)
{
	CAMERA->init(WINSIZEX, WINSIZEY, 1200, 800);
	stage::enter(player);
	_player->setPlayerX(100);
	_player->setPlayerY(WINSIZEY - 150);
	_minX = 0;
	_maxX = 1200;
	_pixelImg = IMAGEMANAGER->findImage("보스전지형처리");

}

void bossStage::enterBoss(boss * boss)
{
	SOUNDMANAGER->stop("필드BGM");
	SOUNDMANAGER->play("보스BGM", 0.7f);

	stage::enterBoss(boss);
	_boss->setBossX(WINSIZEX / 2);
	_boss->setBossY(WINSIZEY / 2);
	_boss->init();
}

void bossStage::exit()
{
}

stage* bossStage::updateStage()
{
	pixelCollision();
	
	CAMERA->setPosition(_player->getPlayerX(), _player->getPlayerY());

	_boss->update();
	return nullptr;
}

void bossStage::render()
{
	IMAGEMANAGER->findImage("보스전배경")->render(getMemDC(), CAMERA->getLeft(), CAMERA->getTop());
	IMAGEMANAGER->findImage("보스전지형처리")->render(getMemDC(), 0, 0);

	_boss->render();
}
