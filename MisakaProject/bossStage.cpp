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

	//Ž���൵ ������Ʈ �Լ��� �־ ����ؼ� �������ش�
	//�÷��̾��� �ȼ��浹 �˻�
	float probePY = pY + _player->getPlayerRectHeight() / 2; //�÷��̾� ��Ʈ�� ���� �κ�

	for (int i = probePY - 5; i < probePY + 5; ++i)
	{
		COLORREF color;
		color = GetPixel(getPixelImage()->getMemDC(), pX, i);

		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if (!(r == 0 && g == 255 && b == 255))
		{
			//�ȼ� ������ �浹
			_player->setPlayerY(i - _player->getPlayerRectHeight() / 2);
			_player->setPlayerGround(true);
			break;
		}
		else _player->setPlayerGround(false);
	}

	//����ĳ���� �ȼ��浹 �˻�
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
			//�ȼ� ������ �浹
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
	_pixelImg = IMAGEMANAGER->findImage("����������ó��");

}

void bossStage::enterBoss(boss * boss)
{
	SOUNDMANAGER->stop("�ʵ�BGM");
	SOUNDMANAGER->play("����BGM", 0.7f);

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
	IMAGEMANAGER->findImage("���������")->render(getMemDC(), CAMERA->getLeft(), CAMERA->getTop());
	IMAGEMANAGER->findImage("����������ó��")->render(getMemDC(), 0, 0);

	_boss->render();
}
