#include "stdafx.h"
#include "enemyManager.h"
#include "enemy.h"
#include "player.h"

enemyManager::enemyManager()
{
}

enemyManager::~enemyManager()
{
}

HRESULT enemyManager::init()
{
	_enemyRespawnPositions = {
		{800, WINSIZEY - 75}, {900, WINSIZEY - 75}, {1000, WINSIZEY - 75}, {1200, WINSIZEY - 75},
		{2000, WINSIZEY - 75}, {2300, WINSIZEY - 75}, {2700, WINSIZEY - 75}, {2900, WINSIZEY - 75},
		{3100, WINSIZEY - 75}, {3300, WINSIZEY - 75}, {3700, WINSIZEY - 75}, {4000, WINSIZEY - 75},
		{4300, WINSIZEY - 75}, {4700, WINSIZEY - 125}, {4800, WINSIZEY - 125}
	};

	return S_OK;
}

void enemyManager::release()
{
	for (int i = 0; i < _vEnemy.size(); i++)
	{
		_vEnemy.erase(_vEnemy.begin() + i);
	}
}

void enemyManager::update()
{
	for (int i = 0; i < _vEnemy.size(); i++)
	{
		_vEnemy[i]->update();
		_vEnemy[i]->move();
	}
	collision();
}

void enemyManager::render()
{
	for (int i = 0; i < _vEnemy.size(); i++)
	{
		_vEnemy[i]->render();
	}
}

void enemyManager::setEnemy()
{
	for (int i = 0; i < _enemyRespawnPositions.size(); i++)
	{
		POINT currPoint = _enemyRespawnPositions[i];
		enemy* newEnemy = new enemy;
		newEnemy->init(currPoint);
		_vEnemy.push_back(newEnemy);
	}

}

void enemyManager::removeEnemy(int arrNum)
{
	_vEnemy.erase(_vEnemy.begin() + arrNum);
}


void enemyManager::collision()
{
	//일반 공격
	if (_player->getPlayerAttack())
	{
		for (int i = 0; i < _vEnemy.size();)
		{
			enemy* currEnemy = _vEnemy[i];
			RECT enemyRec = currEnemy->getRect(); 
			RECT playerRec = _player->getRect();
			RECT temp;
			// 공격받았음
			if(IntersectRect(&temp, &enemyRec, &playerRec))
			{
				removeEnemy(i);
			}
			else
			{
				i++;
			}
		}
	}
	//레일건 공격
	if (_player->getRailgun())
	{
		for (int i = 0; i < _vEnemy.size();)
		{
			enemy* currEnemy = _vEnemy[i];
			RECT enemyRec = currEnemy->getRect();
			RECT railgunRec = _player->getRailgunRect();
			RECT temp;
			// 공격받았음
			if (IntersectRect(&temp, &enemyRec, &railgunRec))
			{
				removeEnemy(i);
			}
			else
			{
				i++;
			}
		}
	}
	////피격
	//if (!_player->getPlayerAttack())
	//{
	//	for (int i = 0; i < _vEnemy.size();)
	//	{
	//		enemy* currEnemy = _vEnemy[i];
	//		RECT enemyRec = currEnemy->getRect();
	//		RECT playerRec = _player->getRect();
	//		RECT temp;
	//		//충돌시 플레이어 피격
	//		if (IntersectRect(&temp, &enemyRec, &playerRec))
	//		{
	//			//_damage = RND->getFromIntTo(8, 16);
	//			//_damage = 10;
	//			//_player->setPlayerHP(_player->getPlayerHP() - _damage);
	//		}
	//		else
	//		{
	//			i++;
	//		}
	//	}
	//}
}
