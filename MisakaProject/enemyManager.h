#pragma once
#include "gameNode.h"

#include <vector>



//������� ���ӹ����� ���� Ŭ���� ���漱��
class enemy;
class player;

class enemyManager : public gameNode
{
private:
	player* _player;

	int _damage;

	//����
	typedef vector<enemy*>				vEnemy;
	typedef vector<enemy*>::iterator	viEnemy;

	//�� ��ü�� ���Ϳ� ����
	vEnemy _vEnemy;
	viEnemy _viEnemy;
	
	vector<POINT> _enemyRespawnPositions/* = {
		{500, WINSIZEY - 75}, {700, WINSIZEY - 75}, {1000, WINSIZEY - 75}, {1200, WINSIZEY - 75},
		{2000, WINSIZEY - 75}, {2300, WINSIZEY - 75}, {2700, WINSIZEY - 75}, {2900, WINSIZEY - 75},
		{3100, WINSIZEY - 75}, {3300, WINSIZEY - 75}, {3700, WINSIZEY - 75}, {4000, WINSIZEY - 75},
		{4400, WINSIZEY - 100}, {4700, WINSIZEY - 100}, {4800, WINSIZEY - 100}
	}*/;

protected:
	
public:
	enemyManager();
	~enemyManager();

	HRESULT init();
	void release();
	void update();
	void render();

	void setEnemy();
	void removeEnemy(int arrNum);
	void setPlayerMemoryAddress(player* player) { _player = player; }

	//�浹�Լ�
	void collision();

	int getEnemyVectorSize() { return _vEnemy.size(); }
	
	/*vector<enemy*> getVMinion() { return _vMinion; }
	vector<enemy*>::iterator getVIMinion() { return _viMinion; }*/

};


