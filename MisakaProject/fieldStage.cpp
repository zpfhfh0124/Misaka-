#include "stdafx.h"
#include "fieldStage.h"
#include "bossStage.h"
#include "player.h"
#include "enemyManager.h"

void fieldStage::pixelCollision()
{
	float pX = _player->getPlayerX();
	float pY = _player->getPlayerY();

	//Ž���൵ ������Ʈ �Լ��� �־ ����ؼ� �������ش�
	float probeY = pY + _player->getPlayerRectHeight() / 2; //�÷��̾� ��Ʈ�� ���� �κ�

	for (int i = probeY - 5; i < probeY + 5; ++i)
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

//�ʱ�ȭ
void fieldStage::enter(player * player)
{
	CAMERA->init(WINSIZEX, WINSIZEY, 5000, 800);

	//�����
	SOUNDMANAGER->play("�ʵ�BGM", 0.7f);

	stage::enter(player);

	_pixelImg = IMAGEMANAGER->findImage("�ʵ�����ó��");
	_isClear = false;
	_minX = 0;
	_maxX = 5000;
	_portal = RectMakeCenter(4800, WINSIZEY - 170, 130, 200);
	_portalImg = IMAGEMANAGER->findImage("��Ż");

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

	//��Ż ����
	RECT temp;
	if (IntersectRect(&temp, &_player->getRect(), &_portal))
	{
		//��Ż ���� �� ���� ���������� ��ȯ
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
	IMAGEMANAGER->findImage("����")->render(getMemDC(), CAMERA->getLeft(), CAMERA->getTop());
	IMAGEMANAGER->findImage("�ٰ�")->render(getMemDC());
	IMAGEMANAGER->findImage("�ʵ�����ó��")->render(getMemDC(), 0, 0);
	_portalImg->render(getMemDC(), _portal.left, _portal.top);
	_enemyMg->render();
	//Rectangle(getMemDC(), _portal);

	/*for (int i = 0; i < FENCEMAX; i++)
	{
		Rectangle(getMemDC(), _fence[i]);
	}*/

	/*char str[128];
	sprintf_s(str, "���� �� : %d", _enemyMg->getEnemyVectorSize());
	TextOut(getMemDC(), CAMERA->getLeft() + 700, 100, str, strlen(str));*/
}
